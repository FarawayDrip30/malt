#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

unsigned int generate_shader(GLenum shader_type, char *shader_source);

unsigned int generate_shader_program();

unsigned int generate_VAO();

int initialise_opengl();