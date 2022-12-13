#ifndef __OPENGL_ENV_HPP
#define __OPENGL_ENV_HPP

#include "renderer.hpp"                 //For now this is to include GLEW
#include "GLFW/glfw3.h"

struct ChessGLConfig{
    
};


class ChessOpenGLEnv{
public:
    ChessOpenGLEnv();
    ChessOpenGLEnv(ChessGLConfig gl_config);

    ~ChessOpenGLEnv();

    int setupStandardGLEnv();
    int refresh_window();   //takes care of rendering and taking input
private:
    GLFWwindow* window;

};

#endif // __OPENGL_ENV_HPP
