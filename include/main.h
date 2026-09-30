#include <portaudio/portaudio.h>


extern int viewport_width;
extern int viewport_height;
extern int viewport_x;
extern int viewport_y;

static int portaudio_test_callback(const void* input_buffer, void* output_buffer, unsigned long frames_per_buffer, 
const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags status_flags, void* user_data);