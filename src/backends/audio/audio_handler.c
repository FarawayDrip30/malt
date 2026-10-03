#include <stdio.h>

#include "backends/audio/audio_handler.h"


struct AudioData audio_stream_data[16];
PaStream* audio_streams[16];
int next_audio_stream = 0;

float music_pitch = 1;
float music_volume = 0.2f;

static int portaudio_callback(const void* input_buffer, void* output_buffer, unsigned long frames_per_buffer, 
const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags status_flags, void* user_data){
    struct AudioData* data = (struct AudioData*) user_data;
    float* out = (float*) output_buffer;
    unsigned int i;
    for(i = 0; i < frames_per_buffer; i++){
        *out++ = data->left_phase * data->volume;
        *out++ = data->right_phase * data->volume;

        // Sawtooth phaser
        data->left_phase += 0.01f * data->pitch;
        // When signal reaches top, drop back down
        if(data->left_phase >= 0.1f ){
            data->left_phase -= 2.0f;
        }
        // Higher pitch to distinguish left and right
        data->left_phase += 0.03f * data->pitch;
        if(data->left_phase >= 0.1f ){
            data->left_phase -= 2.0f;
        }
    }

    return 0;
}

void audio_initialise(){
    PaError err;
    
    err = Pa_Initialize();
    if(err != paNoError){
        printf(  "PortAudio init error: %s\n", Pa_GetErrorText( err ) );
    }
}

int audio_create_stream(){
    PaError err;

    err = Pa_OpenDefaultStream(&audio_streams[next_audio_stream], 0, 2, paFloat32, 44100, 16, portaudio_callback, &audio_stream_data[next_audio_stream]);
    if(err != paNoError){
        printf(  "PortAudio openstream error: %s\n", Pa_GetErrorText( err ) );
    }

    err = Pa_StartStream(audio_streams[next_audio_stream]);
    if(err != paNoError){
        printf(  "PortAudio startstream error: %s\n", Pa_GetErrorText( err ) );
    }

    next_audio_stream++;
    return next_audio_stream - 1;
}

void audio_close_stream(int stream_id){
    PaError err;    

    err = Pa_StopStream(audio_streams[stream_id]);
    if(err != paNoError){
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }

    err = Pa_CloseStream(audio_streams[stream_id]);
    if(err != paNoError){
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }
}

void audio_close_all_streams(){
    for(int i = 0; i < next_audio_stream; i++){
        audio_close_stream(i);
    }
}

void audio_terminate(){
    PaError err;

    audio_close_all_streams();

    err = Pa_Terminate();
    if(err != paNoError){
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }
}


void audio_set_volume(int stream_id, float volume){
    audio_stream_data[stream_id].volume = volume;
}

void audio_set_pitch(int stream_id, float pitch){
    audio_stream_data[stream_id].pitch = pitch;
}