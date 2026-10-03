#pragma oncee

#include <portaudio/portaudio.h>

struct AudioData {
    float left_phase;
    float right_phase;
};

extern PaStream* audio_stream;

extern float music_pitch;
extern float music_volume;

static int portaudio_callback(const void* input_buffer, void* output_buffer, unsigned long frames_per_buffer, 
const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags status_flags, void* user_data);

void audio_initialise();
void audio_terminate();