#include <stdio.h>
//#include <windows.h>
#include <GLFW/glfw3.h>
#include <portaudio/portaudio.h>

#include "backends/system/system_handler.h"

void system_sleep(int ms){
    //Sleep(ms);
    //Pa_Sleep(ms);
    glfwWaitEventsTimeout((float) ms / 1000.0f);
}

int system_get_time(){
    return glfwGetTime() * 1000;
}
float system_get_time_seconds_float(){
    return glfwGetTime();
}