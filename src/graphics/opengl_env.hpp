#ifndef __OPENGL_ENV_HPP
#define __OPENGL_ENV_HPP

#include "graphics/renderer.hpp"                 //For now this is to include GLEW
#include "graphics/utils.hpp"

#include "chess/game_board.hpp"
#include "chess/pieces.hpp"


#include "GLFW/glfw3.h"

struct ChessGLConfig{
    
};


class ChessOpenGLEnv{
public:
    ChessOpenGLEnv();
    ChessOpenGLEnv(ChessGLConfig gl_config);

    ~ChessOpenGLEnv();

    void processInput();
    int loadBasicGLEnv();
    int initialize(const GameBoard& board, const Pieces& pieces, float scale);
    int refresh_window();   //takes care of rendering and taking input
private:
    GLFWwindow* window;
    int window_width;
    int window_height;

    float window_scale;
    float refresh_rate;

    Color clear_color;
    Renderer renderer;

};

#endif // __OPENGL_ENV_HPP
