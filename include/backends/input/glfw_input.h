#pragma once

#include <stdbool.h>

#include "backends/graphics/opengl_backend.h"

void glfw_key_pressed(GLFWwindow* window, int key, int scan_code, int action, int mods);
void glfw_mouse_button_pressed(GLFWwindow* window, int button, int action, int mods);
void glfw_cursor_position(GLFWwindow* window, double x, double y);

void glfw_input_initialise();
void glfw_input_update();

void print_input_down();


enum input_down_enum {
	forwards, 
	backwards, 
	left, 
	right, 
	up, 
	down,
	pause,
	fire1,
	fire2
};
enum input_vector_enum {
	mouse
};

