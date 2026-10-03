#include <stdio.h>

#include "backends/audio/audio_handler.h"

float music_pitch = 1;
float music_volume = 0.2f;

static int portaudio_callback(const void* input_buffer, void* output_buffer, unsigned long frames_per_buffer, 
const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags status_flags, void* user_data){
    struct AudioData* data = (struct AudioData*) user_data;
    float* out = (float*) output_buffer;
    unsigned int i;
    for(i = 0; i < frames_per_buffer; i++){
        *out++ = data->left_phase * music_volume;
        *out++ = data->right_phase * music_volume;

        // Sawtooth phaser
        data->left_phase += 0.01f* music_pitch;
        // When signal reaches top, drop back down
        if(data->left_phase >= 0.1f ){
            data->left_phase -= 2.0f;
        }
        // Higher pitch to distinguish left and right
        data->left_phase += 0.03f* music_pitch;
        if(data->left_phase >= 0.1f ){
            data->left_phase -= 2.0f;
        }
    }

    return 0;
}
    
PaStream* audio_stream;

void audio_initialise(){
    PaError err;
    
    err = Pa_Initialize();
    if(err != paNoError){
        printf(  "PortAudio init error: %s\n", Pa_GetErrorText( err ) );
    }

    
    struct AudioData data;
    err = Pa_OpenDefaultStream(&audio_stream, 0, 2, paFloat32, 44100, 256, portaudio_callback, &data);
    if(err != paNoError){
        printf(  "PortAudio openstream error: %s\n", Pa_GetErrorText( err ) );
    }

    err = Pa_StartStream(audio_stream);
    if(err != paNoError){
        printf(  "PortAudio startstream error: %s\n", Pa_GetErrorText( err ) );
    }
}

void audio_terminate(){
    PaError err;

    err = Pa_StopStream(audio_stream);
    if(err != paNoError){
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }

    err = Pa_CloseStream(audio_stream);
    if(err != paNoError){
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }

    err = Pa_Terminate();
    if(err != paNoError){
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }
}