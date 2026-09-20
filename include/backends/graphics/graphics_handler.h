#include <stdbool.h>
#include <stdint.h>

#include "gameobject.h"


struct GraphicsHandler{
    int (*initialise)();
    void (*render_start)();
    void (*render_finish)();
    void (*terminate)();

    unsigned int (*generate_texture)(struct TextureData*);
    void (*render_gameobject)(struct GameObject*);

    bool (*should_window_close)();
};

struct TextureData{
    int width;
    int height;
    int nr_channels;

    unsigned char* data;
};

struct TextureData* load_texture_data(char* texture_path);
void free_texture_data(struct TextureData* texture_data);

struct RGBAPixel{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

extern struct GraphicsHandler opengl_graphics;