#pragma oncee

#include <portaudio/portaudio.h>

struct AudioData {
    float left_phase;
    float right_phase;

    float volume;
    float pitch;
};

extern float music_pitch;
extern float music_volume;

static int portaudio_callback(const void* input_buffer, void* output_buffer, unsigned long frames_per_buffer, 
const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags status_flags, void* user_data);

void audio_initialise();

int audio_create_stream();
void audio_close_stream(int stream_id);
void audio_close_all_streams();

void audio_terminate();



void audio_set_volume(int stream_id, float volume);
void audio_set_pitch(int stream_id, float pitch);