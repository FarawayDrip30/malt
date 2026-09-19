#include <stdbool.h>
#include <stdint.h>

struct GraphicsHandler{
    int (*initialise)();
    void (*render_loop)();
    void (*terminate)();

    bool (*should_window_close)();
};

struct TextureData{
    int width;
    int height;
    int nr_channels;

    unsigned char* data;
};

struct RGBAPixel{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

extern struct GraphicsHandler opengl_graphics;