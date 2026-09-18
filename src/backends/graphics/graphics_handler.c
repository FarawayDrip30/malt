#include "backends/graphics/graphics_handler.h"
#include "backends/graphics/opengl_backend.h"

struct GraphicsHandler opengl_graphics = {
    &opengl_initialise,
    &opengl_renderloop,
    &opengl_terminate,

    &opengl_should_close,
};