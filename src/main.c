#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "backends/graphics/graphics_handler.h"
#include "backends/input/glfw_input.h"
#include "backends/audio/audio_handler.h"
#include "main.h"

#include <GLFW/glfw3.h>


struct GameObject* bg;
struct GameObject* player;

int viewport_width = 600;
int viewport_height = 600;
int viewport_x = 0;
int viewport_y = 0;


int main(){
    printf("Hello, World!\n");

    audio_initialise();

    struct GraphicsHandler* graphics_handler = &opengl_graphics;

    graphics_handler->initialise();

    glfw_input_initialise();

    struct TextureData* wall_tex_data = load_texture_data("res/img/wall.jpg");
    unsigned int wall_tex_id = graphics_handler->generate_texture(wall_tex_data);

    struct TextureData* grin_tex_data = load_texture_data("res/img/toothygrin.jpg");
    unsigned int grin_tex_id = graphics_handler->generate_texture(grin_tex_data);

    bg = create_gameobject(0.0f, 0.0f, 600.0f, 600.0f, 0.0f, 0.0f, wall_tex_id);
    player = create_gameobject(0.0f, 0.0f, 64.0f, 64.0f, 0.0f, 0.0f, grin_tex_id);

    while(!graphics_handler->should_window_close()){
        // Update
        glfw_input_update();
        //print_input_down();

        // Modulate that crazy crazy sound
        music_pitch = sin(glfwGetTime() * (2 * sin(glfwGetTime() / 4))) * 5 + 6;

        set_gameobject_pos(player, 0, sin(glfwGetTime()) * 100);

        // Render
        graphics_handler->render_start();
        
        graphics_handler->render_gameobject(bg);
        graphics_handler->render_gameobject(player);

        graphics_handler->render_finish();
    }

    audio_terminate();

    graphics_handler->terminate();

    free_texture_data(wall_tex_data);
    free_texture_data(grin_tex_data);

    return 0;
}
