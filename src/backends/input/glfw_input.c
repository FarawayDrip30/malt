#include "backends/input/glfw_input.h"



int input_down[] = {
	0, // 0 - Forwards
    0, // 1 - Backwards
    0, // 2 - Left
    0, // 3 - Right
    0, // 4 - Up
    0, // 5 - Down
    0, // 6 - Pause
    0, // 7 - Fire1
    0, // 8 - Fire2
};
float input_vector[][2] = {
	{ 0.0f, 0.0f }
};

int key_map[][2] = {
    // e.g. Key W sets input_down[0 (forwards)] to 1 when pressed, 0 when not
	{GLFW_KEY_W, forwards},
	{GLFW_KEY_S, backwards},
	{GLFW_KEY_A, left},
	{GLFW_KEY_D, right},
	{GLFW_KEY_SPACE, up},
	{GLFW_KEY_LEFT_SHIFT, down},
	{GLFW_KEY_ESCAPE, pause}
};
int mouse_map[][2] = {
    {GLFW_MOUSE_BUTTON_LEFT, fire1},
    {GLFW_MOUSE_BUTTON_RIGHT, fire2}
};
#define ALL_JOYSTICKS -1
int controller_map[][3] = {
    {GLFW_GAMEPAD_BUTTON_A, up, ALL_JOYSTICKS},
    // TODO: having 2 controller buttons on one input means it will always be zero as it is fetched every frame and might be 0.
    //{GLFW_GAMEPAD_BUTTON_LEFT_THUMB, down, ALL_JOYSTICKS},
    //{GLFW_GAMEPAD_BUTTON_RIGHT_THUMB, down, ALL_JOYSTICKS},
    {GLFW_GAMEPAD_BUTTON_LEFT_THUMB, down, ALL_JOYSTICKS},
    {GLFW_GAMEPAD_BUTTON_X, fire1, ALL_JOYSTICKS},
    {GLFW_GAMEPAD_BUTTON_Y, fire2, ALL_JOYSTICKS},
};

void glfw_key_pressed(GLFWwindow* window, int key, int scan_code, int action, int mods){
    if (action == GLFW_PRESS || action == GLFW_RELEASE) {
		for (int i = 0; i < sizeof(key_map) / sizeof(key_map[0]); i++) {
			if (key_map[i][0] == key) {
				input_down[key_map[i][1]] = action;
                // Don't return in case this key is binded to other input downs
			}
		}
	}
}
void glfw_mouse_button_pressed(GLFWwindow* window, int button, int action, int mods){
    if (action == GLFW_PRESS || action == GLFW_RELEASE) {
		for (int i = 0; i < sizeof(mouse_map) / sizeof(mouse_map[0]); i++) {
			if (mouse_map[i][0] == button) {
				input_down[mouse_map[i][1]] = action;
                // Don't return in case this button is binded to other input downs
			}
		}
	}
}
void glfw_cursor_position(GLFWwindow* window, double x, double y){
    input_vector[mouse][0] = x;
	input_vector[mouse][1] = y;
}

void glfw_input_update(){
    for(int j = 0; j < GLFW_JOYSTICK_LAST; j++){
        int count;
        const unsigned char* buttons = glfwGetJoystickButtons(j, &count);

        // If controller is plugged in
        if(buttons != NULL){
            /*
            for(int i = 0; i < count; i++){
                printf(" %i:%i ", i, buttons[i]);
            }
            */
            for (int i = 0; i < sizeof(controller_map) / sizeof(controller_map[0]); i++) {
                // Ensure the controller we're currently checking (j) should control this input
                if(controller_map[i][2] == ALL_JOYSTICKS || controller_map[i][2] == j){
                    input_down[controller_map[i][1]] = buttons[controller_map[i][0]];
                    // Don't return in case this button is binded to other input downs

                    //printf(" %i %i %i %i %i %i |||| ", down, i, controller_map[i][1], controller_map[i][0], buttons[controller_map[i][0]], buttons[10]);
                }
            }
        }
    }
}

void glfw_input_initialise(){
    glfwSetKeyCallback(opengl_window, glfw_key_pressed);
    glfwSetMouseButtonCallback(opengl_window, glfw_mouse_button_pressed);
    glfwSetCursorPosCallback(opengl_window, glfw_cursor_position);
}

void print_input_down(){
    printf("Input Down: ");
    for(int i = 0; i < sizeof(input_down) / sizeof(input_down[0]); i++){
        printf("%i: %i, ", i, input_down[i]);
    }
    printf("\n");
}
