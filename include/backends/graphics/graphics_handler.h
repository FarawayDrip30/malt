#include <stdbool.h>

struct GraphicsHandler{
    int (*initialise)();
    void (*render_loop)();
    void (*terminate)();

    bool (*should_window_close)();
};

extern struct GraphicsHandler opengl_graphics;