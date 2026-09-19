#include <stdio.h>

#include "backends/graphics/graphics_handler.h"
#include "backends/graphics/opengl_backend.h"

struct GraphicsHandler opengl_graphics = {
    &opengl_initialise,
    &opengl_renderloop,
    &opengl_terminate,

    &opengl_should_close,
};


struct RGBAPixel get_pixel_from_texture_data(struct TextureData texture_data, int x, int y){
    if(x < 0 || y < 0 || x > texture_data.width || y > texture_data.height){
        printf("Pixel outside of Texture Coordinates.");
        struct RGBAPixel out = { 0, 0, 0, 255 };
        return out;
    }

    int pixel_data_start = x * y * texture_data.nr_channels;

    if(texture_data.nr_channels == 3){
        struct RGBAPixel out = { texture_data.data[pixel_data_start], texture_data.data[pixel_data_start+1], texture_data.data[pixel_data_start+2], 255 };
        return out;
    }
    else if(texture_data.nr_channels == 4){
        struct RGBAPixel out = { texture_data.data[pixel_data_start], texture_data.data[pixel_data_start+1], texture_data.data[pixel_data_start+2], texture_data.data[pixel_data_start+3] };
        return out;
    }
}

void print_texture_data(struct TextureData texture_data){
    for(int i = 0; i < texture_data.width * texture_data.height * texture_data.nr_channels; i += texture_data.nr_channels){
        if(texture_data.nr_channels == 3){
            printf("r: %i, g: %i, b: %i\n", texture_data.data[i], texture_data.data[i+1], texture_data.data[i+2]);
        }
        else if(texture_data.nr_channels == 4){
            printf("r: %i, g: %i, b: %i, a: %i\n", texture_data.data[i], texture_data.data[i+1], texture_data.data[i+2], texture_data.data[i+3]);
        }
    }
}