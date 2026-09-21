#include "backends/input/glfw_input.h"

void glfw_key_pressed(GLFWwindow* window, int key, int scan_code, int action, int mods){
    printf("Key: %i\n", key);
}

void glfw_input_initialise(){
    glfwSetKeyCallback(opengl_window, glfw_key_pressed);
}



bool glfw_input_left_pressed(){

}