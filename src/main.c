#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

//#include <portaudio/portaudio.h>

#include "backends/graphics/graphics_handler.h"
#include "backends/input/glfw_input.h"

#include <GLFW/glfw3.h>


struct GameObject* bg;
struct GameObject* player;

int viewport_width = 600;
int viewport_height = 600;
int viewport_x = 0;
int viewport_y = 0;

struct AudioData {
    float left_phase;
    float right_phase;
};

/*
static int portaudio_callback(const void* input_buffer, void* output_buffer, unsigned long frames_per_buffer, 
const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags status_flags, void* user_data){
    struct AudioData* data = (struct AudioData*) user_data;
    float* out = (float*) output_buffer;

    for(int i = 0; i < frames_per_buffer; i++){
        *out++ = data->left_phase;
        *out++ = data->right_phase;

        // Sawtooth phaser
        data->left_phase += 0.01f;
        // When signal reaches top, drop back down
        if(data->left_phase >= 1.0f){
            data->left_phase -= 2.0f;
        }
        // Higher pitch to distinguish left and right
        data->left_phase += 0.03f;
        if(data->left_phase >= 1.0f){
            data->left_phase -= 2.0f;
        }
    }

    return 0;
}
    */

int main(){
    printf("Hello, World!\n");

    //PaError err;
    /*
    err = Pa_Initialize();
    if(err != paNoError){
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }

    PaStream* stream;
    struct AudioData data;
    err = Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, 44100, 256, portaudio_callback, &data);
    if(err != paNoError){
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }

    err = Pa_StartStream(&stream);
    if(err != paNoError){
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }

    Pa_Sleep(5000);

    err = Pa_StopStream(&stream);
    if(err != paNoError){
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }

    err = Pa_CloseStream(&stream);
    if(err != paNoError){
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }
        */

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

    /*
    err = Pa_Terminate();
    if(err != paNoError){
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }
        */

    return 0;
}
