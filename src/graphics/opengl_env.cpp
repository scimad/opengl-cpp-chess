#include "graphics/opengl_env.hpp"
#include "graphics/renderer.hpp"
#include "graphics/utils.hpp"

#include "chess/game_board.hpp"
#include "chess/pieces.hpp"

#include "ZR/core.hpp"

ChessOpenGLEnv::~ChessOpenGLEnv(){
    zr::log("Destroying OpenGL context and all. Terminating.");
    glfwTerminate();
}

ChessOpenGLEnv::ChessOpenGLEnv(){
    window_scale = 1.0;                                 //default scale of window
    window_height = 640;
    window_width = 640;

    clear_color = Color(0.2f, 0.2f, 0.2f, 0.0f);        //default color to clear

    if(loadBasicGLEnv() != 0){
        zr::log("Setting up OpenGL Environment failed.");
        exit(0);
    };
}

int ChessOpenGLEnv::refresh_window(){
    int exit_flag = glfwWindowShouldClose(window);
    processInput(window);
    glfwSwapBuffers(window);
    // renderer.clear();
    glfwPollEvents();
    return exit_flag;
}

ChessOpenGLEnv::ChessOpenGLEnv(ChessGLConfig gl_config){
    // loadBasicGLEnv();
}

int ChessOpenGLEnv::initialize(const GameBoard& board, const Pieces& pieces, float scale){
    window_scale = scale;
    window_width = (int) window_scale* board.width_ratio;
    window_height = (int) window_scale * board.height_ratio;
    glfwSetWindowSize(window, window_width, window_height);

    //Now render board texture
    return 0;
}

int ChessOpenGLEnv::loadBasicGLEnv(){
    zr::log_level = zr::VERBOSITY_LEVEL::DEBUG;
    if (!glfwInit()){
        zr::log("GLFW initialization failed.", zr::VERBOSITY_LEVEL::ERROR);
        return -1;
    }
    zr::log("Successfully initialized GLFW.");

    // Choose OpenGL version and setup either compatibility profile or core profile 
    GLCALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
    GLCALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
    GLCALL(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));      // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLCALL(window = glfwCreateWindow(window_width, window_height, "OpenGL-CPP Chess", NULL, NULL));

    if (!window){
        zr::log("Failed to create GLFW window.", zr::VERBOSITY_LEVEL::ERROR);
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    zr::log("Successfully created GLFW window.");

    // glfwSwapInterval(1);

    // Initialize GLEW
    GLenum err = glewInit();                      //Must do after glfwMakeContextCurrent() or alternatively after properly initializing GLUT
    if (GLEW_OK != err){
        zr::log("Failed to initialize GLEW. Err: " + std::string((const char*)(glewGetErrorString(err))), zr::VERBOSITY_LEVEL::WARNING);
        glfwTerminate();
        return -1;
    }
    zr::log("Successfully initialized GLEW.");
    zr::log("OpenGL Version: " + std::string((const char*) glGetString(GL_VERSION)));

    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);

    
        // This gives transparency to transparent regions of pngs
    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Succesfully setup OpenGL Env
    return 0;
}
