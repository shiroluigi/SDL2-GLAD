#pragma once
#include <SDL2/SDL.h>
#include <glad/gl.h>
#include <reader.h>

class Globals{
    public:
        inline static int gScreenHeight = 480;
        inline static int gScreenWidth = 640;
        inline static SDL_Window* gApplicationWindow = nullptr;
        inline static SDL_GLContext gOpenGLContext = nullptr;
        inline static bool quit = false;
        inline static GLuint gVertexArrayObj = 0;
        inline static GLuint gVertexBufferObject = 0;
        inline static GLuint gGraphicsPipelineShaderProgram = 0;
        inline static GLuint gIndexBufferObject = 0;
};