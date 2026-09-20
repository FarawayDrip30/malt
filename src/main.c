#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <backends/graphics/graphics_handler.h>


struct GameObject* player;

int main(){
    printf("Hello, World!\n");

    struct GraphicsHandler* graphics_handler = &opengl_graphics;

    graphics_handler->initialise();

    struct TextureData* player_tex_data = load_texture_data("res/img/wall.jpg");
    unsigned int player_tex_id = graphics_handler->generate_texture(player_tex_data);
    player = create_gameobject(0.0f, 0.0f, 0.0f, 0, player_tex_id);

    while(!graphics_handler->should_window_close()){
        // Update
        set_gameobject_pos(player, 0, sin(time(NULL)));

        // Render
        graphics_handler->render_start();
        
        graphics_handler->render_gameobject(player);

        graphics_handler->render_finish();
    }

    graphics_handler->terminate();
    free_texture_data(player_tex_data);

    return 0;
}
