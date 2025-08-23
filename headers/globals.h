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
        // inline static std::string gVertexShaderSource = 
        //     "#version 410 core\n"
        //     "in vec4 position;\n"
        //     "void main(){\n"
        //     "gl_Position = vec4(position.x,position.y,position.z,position.w);\n"
        //     "}\n";
        // inline static std::string gFragmentShaderSource = 
        //     "#version 410 core\n"
        //     "out vec4 color;\n"
        //     "void main(){\n"
        //     "color = vec4(1.0f,0.5f,0.0f,1.0f);\n"
        //     "}\n";
        inline static std::string shaderPathInitials = "./shader/";
};