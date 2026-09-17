#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    //1, 2, 3   // second Triangle
};

char vertex_shader_source[1024];
char fragment_shader_source[1024];


void load_string_from_file(char* output, char* path, int string_size){
    FILE *fptr;
    fptr = fopen(path, "r");
    char short_string[100];
    char file_string[string_size];
    
    // Clear file_string, else last file's read is kept in memory
    strncpy(file_string, "", sizeof(file_string));
    
    while(fgets(short_string, 100, fptr)){
        sprintf(file_string, "%s%s", file_string, short_string);
    }
    fclose(fptr);

    strncpy(output, file_string, strlen(file_string)+1);

}
void load_shaders(){
    load_string_from_file(vertex_shader_source, "res/shaders/vertex_shader.glsl", 1024);
    load_string_from_file(fragment_shader_source, "res/shaders/fragment_shader.glsl", 1024);
}

unsigned int generate_shader(GLenum shader_type, char *shader_source){
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

unsigned int generate_shader_program(){
    // Make vertex shader from vertex_shader_source
    unsigned int vertex_shader = generate_shader(GL_VERTEX_SHADER, vertex_shader_source);
    // Make fragment shader from fragment_shader_source
    unsigned int fragment_shader = generate_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

    unsigned int shader_program;
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

unsigned int generate_VAO(){
    // Vertex Array Object
    // Contains enable/disable vertexattribarray, vertex attribute configs,
    // and attribute pointers to attributes in VBOs
    unsigned int VAO;
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
    // Vec3, Data type, Normalize, stride, offset from where data begins
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    return VAO;
}

int main(){
    printf("Hello, World!\n");

    load_shaders();

    // Init GLFW, tell it what OpenGL Version & Mode we're using
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "malt", NULL, NULL);
    if(window == NULL){ printf("Failed to Create GLFW Widnow\n"); glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    // Init GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { printf("Failed to Initialise GLAD\n"); return -1; }

    // Tell OpenGL how big the window is
    glViewport(0, 0, 800, 600);
    // Function to call on window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int shader_program = generate_shader_program();
    glUseProgram(shader_program);

    unsigned int VAO = generate_VAO();

    while(!glfwWindowShouldClose(window)){
        processInput(window);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        
        glBindVertexArray(VAO);
        
        // We're drawing 2 triangles (6 indices), indices are ints, no offset.
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}