#pragma once

#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "gameobject.h"
#include "backends/graphics/graphics_handler.h"

void framebuffer_size_callback(GLFWwindow* _window, int width, int height);
void processInput(GLFWwindow *_window);

unsigned int generate_shader(GLenum shader_type, char *shader_source);
unsigned int generate_shader_program();

unsigned int generate_VAO();

unsigned int opengl_generate_texture(struct TextureData* texture_data);

int opengl_initialise();
void opengl_render_start();
void opengl_render_finish();
void opengl_terminate();

void opengl_render_gameobject(struct GameObject* go);

bool opengl_should_close();