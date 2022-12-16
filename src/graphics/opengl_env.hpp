#ifndef __OPENGL_ENV_HPP
#define __OPENGL_ENV_HPP

#include "graphics/renderer.hpp"                 //For now this is to include GLEW
#include "graphics/utils.hpp"

#include "chess/game_board.hpp"
#include "chess/pieces.hpp"

#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct ChessGLConfig{
    
};



// class ChessOpenGLEnv{
// public:
//     ChessOpenGLEnv();
//     ChessOpenGLEnv(ChessGLConfig gl_config);

//     ~ChessOpenGLEnv();

//     void GLunbindShaderVertexIndexBuffer();
//     void processInput();
//     int loadBasicGLEnv();
//     int initialize(const GameBoard& board, const Pieces& pieces, float scale);
//     int display(GameBoard& board, const Pieces& pieces);   //takes care of rendering and taking input
// private:
//     GLFWwindow* window;
//     int window_width;
//     int window_height;

//     float window_scale;
//     float refresh_rate;

//     glm::mat4 proj, view, model, mvp;

//     Color clear_color;
//     Renderer renderer;
//     Shader shader;

// };


class ChessOpenGLEnv{
public:
    ChessOpenGLEnv();
    GLFWwindow* window;
    int initialize();
};

#endif // __OPENGL_ENV_HPP
