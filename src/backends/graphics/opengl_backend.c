#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "utils/file_utils.h"
#include "backends/graphics/opengl_backend.h"


float vertices[] = {
    // positions         // colors          // texture coordinates
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,     // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,     // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.5f, 0.0f,     // top 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 2,  // first Triangle
    //1, 2, 3   // second Triangle
};

char vertex_shader_source[1024];
char fragment_shader_source[1024];

unsigned int shader_program;
unsigned int VAO;

void opengl_load_shaders(){
    load_string_from_file(vertex_shader_source, "res/shaders/vertex_shader.glsl", 1024);
    load_string_from_file(fragment_shader_source, "res/shaders/fragment_shader.glsl", 1024);
}

unsigned int opengl_generate_shader(GLenum shader_type, char *shader_source){
    unsigned int shader;
    shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, & (const char*) { shader_source }, NULL);
    glCompileShader(shader);

    // Check it worked
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) { 
        char infoLog[512]; 
        glGetShaderInfoLog(shader, 512, NULL, infoLog); 
        printf("Shader compilation failed: \n%s\n", infoLog); 
        return 0;
    }

    return shader;
}

unsigned int opengl_generate_shader_program(){
    // Make vertex shader from vertex_shader_source
    unsigned int vertex_shader = opengl_generate_shader(GL_VERTEX_SHADER, vertex_shader_source);
    // Make fragment shader from fragment_shader_source
    unsigned int fragment_shader = opengl_generate_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

    //unsigned int shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    int success;
    if(!success) { 
        char infoLog[512]; 
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog); 
        printf("Shader program compilation failed: \n%s\n", infoLog); 
        return 0;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}

unsigned int opengl_generate_vao(){
    // Vertex Array Object
    // Contains enable/disable vertexattribarray, vertex attribute configs,
    // and attribute pointers to attributes in VBOs
    //unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // All stuff below is bounded to this VAO now.
    glBindVertexArray(VAO);

    // Vertex Buffer Object (Stores Vertices)
    unsigned int VBO;
    // Generate 1 buffer, store created buffer object name in VBO
    glGenBuffers(1, &VBO);
    // Set VBO var to be an array buffer
    // After this, any GL_ARRAY_BUFFER refers to & modifies VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // GL_STATIC_DRAW says that the data is only set once and used many times
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Element Buffer Objects (Stores indices of vertices for triangles)
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Arguments:
    // Which attribute position we want to configure (data will go into the shader in layout (location = 0) e.g. in vertex shader),
    // Index, Vec3, Data type, Normalize, stride, offset from where data begins
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    return VAO;
}

unsigned int opengl_generate_texture(char* tex_path){
    // Load texture from file
    int tex_width, tex_height, tex_nrChannels;
    unsigned char* tex_data = stbi_load(tex_path, &tex_width, &tex_height, &tex_nrChannels, 0); 
    if(!tex_data){ printf("Failed to load texture."); }

    // Generate texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLenum img_format;
    if(tex_nrChannels == 3){
        img_format = GL_RGB;
    }
    else{
        img_format = GL_RGBA;
    }

    // Is texture 2d, mipmaps (we aren't manually adding them so 0), format, width, height, legacy shit, format of source image (e.g. GL_RGB), datatype of source image, image data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, img_format, GL_UNSIGNED_BYTE, tex_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(tex_data);
    
    return texture;
}

GLFWwindow* opengl_window;
unsigned int wall_texture;
unsigned int awesomeface_texture;
unsigned int transform_loc;

int opengl_initialise(){
    opengl_load_shaders();

    // Init GLFW, tell it what OpenGL Version & Mode we're using
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window
    opengl_window = glfwCreateWindow(600, 600, "malt", NULL, NULL);
    if(opengl_window == NULL){ printf("Failed to Create GLFW Widnow\n"); glfwTerminate(); return -1; }
    glfwMakeContextCurrent(opengl_window);

    // Init GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { printf("Failed to Initialise GLAD\n"); return -1; }

    // Tell OpenGL how big the window is
    glViewport(0, 0, 600, 600);
    // Function to call on window resize
    glfwSetFramebufferSizeCallback(opengl_window, framebuffer_size_callback);

    // Set texture settings
    // Textures repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Texture scaling (minifying, magnifying)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    wall_texture = opengl_generate_texture("res/img/wall.jpg");
    //opengl_generate_texture("res/img/read_test.png");
    awesomeface_texture = opengl_generate_texture("res/img/awesomeface.png");

    unsigned int shader_program = opengl_generate_shader_program();
    glUseProgram(shader_program);

    // Set which GL_TEXTUREX each shader variable maps to
    glUniform1i(glGetUniformLocation(shader_program, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shader_program, "texture2"), 1);

    unsigned int VAO = opengl_generate_vao();

    /*
    vec4 vec = {1.0f, 0.0f, 0.0f, 1.0f};
    mat4 trans;
    glm_mat4_identity(trans);
    vec3 trans_vec = {1.0f, 1.0f, 0.0f};
    glm_translate(trans, trans_vec);
    glm_mat4_mulv(trans, vec, vec);
    glm_vec4_print(vec, stdout);
    */

    transform_loc = glGetUniformLocation(shader_program, "transform");
}


void opengl_renderloop(){
    processInput(opengl_window);

    // Render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    mat4 trans;
    glm_mat4_identity(trans);
    vec3 rot_axis = {0.0f, 0.0f, 1.0f};
    vec3 scale = {sin(glfwGetTime()), sin(glfwGetTime()), 1.0f};
    vec3 translate = {sin(glfwGetTime()), sin(glfwGetTime()), 1.0f};
    glm_rotate(trans, (float)glfwGetTime(), rot_axis);
    glm_scale(trans, scale);
    glm_translate(trans, translate);

    glUniformMatrix4fv(transform_loc, 1, GL_FALSE, (float*) trans);

    glUseProgram(shader_program);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, wall_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, awesomeface_texture);

    glBindVertexArray(VAO);
    
    // We're drawing 2 triangles (6 indices), indices are ints, no offset.
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(opengl_window);
    glfwPollEvents();
}

void opengl_terminate(){
    glfwTerminate();
}

bool opengl_should_close(){
    return glfwWindowShouldClose(opengl_window);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}