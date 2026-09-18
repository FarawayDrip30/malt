#include <stdio.h>
#include <stdbool.h>

#include <backends/graphics/graphics_handler.h>
#include <backends/graphics/opengl_backend.h>

int main(){
    printf("Hello, World!\n");

    struct GraphicsHandler graphics_handler = opengl_graphics;

    graphics_handler.initialise();

    while(!graphics_handler.should_window_close()){
        graphics_handler.render_loop();
    }

    graphics_handler.terminate();

    return 0;
}
