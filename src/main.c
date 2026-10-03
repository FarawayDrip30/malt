#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "backends/graphics/graphics_handler.h"
#include "backends/input/glfw_input.h"
#include "backends/audio/audio_handler.h"
#include "backends/system/system_handler.h"
#include "main.h"

#include <GLFW/glfw3.h>


struct GameObject* bg;
struct GameObject* player;

int viewport_width = 600;
int viewport_height = 600;
int viewport_x = 0;
int viewport_y = 0;

int music_stream;
int sfx_stream;

int sfx_timer = -1;

void play_sound(float pitch, int frames){
    audio_set_pitch(sfx_stream, pitch);
    audio_set_volume(sfx_stream, 0.5f);
    sfx_timer = frames;
}

int main(){
    printf("Hello, World!\n");

    audio_initialise();

    music_stream = audio_create_stream();
    sfx_stream = audio_create_stream();

    audio_set_volume(music_stream, 0.2f);
    audio_set_pitch(sfx_stream, 5.5f);

    struct GraphicsHandler* graphics_handler = &opengl_graphics;

    graphics_handler->initialise();

    glfw_input_initialise();

    struct TextureData* wall_tex_data = load_texture_data("res/img/wall.jpg");
    unsigned int wall_tex_id = graphics_handler->generate_texture(wall_tex_data);

    struct TextureData* grin_tex_data = load_texture_data("res/img/toothygrin.jpg");
    unsigned int grin_tex_id = graphics_handler->generate_texture(grin_tex_data);

    bg = create_gameobject(0.0f, 0.0f, 600.0f, 600.0f, 0.0f, 0.0f, wall_tex_id);
    player = create_gameobject(0.0f, 0.0f, 64.0f, 64.0f, 0.0f, 0.0f, grin_tex_id);

    int fps = 60;
    int fps_wait = 1000 / fps;

    int frame_start;
    int frame_end;
    int frame_difference;

    bool process_game = true;

    while(true){
        if(process_game){
            frame_start = system_get_time();

            // Update
            glfw_input_update();
            //print_input_down();

            if(input_down[fire1]){
                play_sound(1.0f, 1);
            }

            // Modulate that crazy crazy sound
            audio_set_pitch(music_stream, sin(((float)system_get_time() / 1000.0f) * (2.0f * sin(((float)system_get_time() / 1000.0f) / 4.0f))) * 5.0f + 6.0f);
            
            if(sfx_timer >= 0){
                sfx_timer--;
                if(sfx_timer < 0){
                    audio_set_volume(sfx_stream, 0);
                }
            }

            set_gameobject_pos(player, 0, sin(((float)system_get_time() / 1000.0f)) * 100);

            // Render
            graphics_handler->render_start();
                
            graphics_handler->render_gameobject(bg);
            graphics_handler->render_gameobject(player);

            graphics_handler->render_finish();
                
            if(graphics_handler->should_window_close()){ break; }
        }
        
        // Ensure game runs at 60fps
        frame_end = system_get_time();
        frame_difference = frame_end - frame_start;
        if(frame_difference < fps_wait){
            process_game = false;
            system_sleep(fps_wait - frame_difference);
        }
        else{
            process_game = true;
        }
    }

    audio_terminate();

    graphics_handler->terminate();

    free_texture_data(wall_tex_data);
    free_texture_data(grin_tex_data);

    return 0;
}
