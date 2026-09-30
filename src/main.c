#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "backends/graphics/graphics_handler.h"
#include "backends/input/glfw_input.h"

#include <GLFW/glfw3.h>


struct GameObject* bg;
struct GameObject* player;

int main(){
    printf("Hello, World!\n");

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
        set_gameobject_pos(player, 0, sin(glfwGetTime()) * 100);

        // Render
        graphics_handler->render_start();
        
        graphics_handler->render_gameobject(bg);
        graphics_handler->render_gameobject(player);

        graphics_handler->render_finish();
    }

    graphics_handler->terminate();

    free_texture_data(wall_tex_data);
    free_texture_data(grin_tex_data);

    return 0;
}
