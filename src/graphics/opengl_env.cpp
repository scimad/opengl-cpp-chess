#include "graphics/opengl_env.hpp"
#include "graphics/renderer.hpp"
#include "graphics/utils.hpp"

#include "ZR/core.hpp"

ChessOpenGLEnv::~ChessOpenGLEnv(){
    zr::log("Destroying OpenGL context and all. Terminating.");
    glfwTerminate();
}

ChessOpenGLEnv::ChessOpenGLEnv(){
    setupStandardGLEnv();
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
    // setupStandardGLEnv();
}

int ChessOpenGLEnv::setupStandardGLEnv(){

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

    GLCALL(window = glfwCreateWindow(960, 540, "OpenGL-CPP Chess", NULL, NULL));

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

    glClearColor(0.2, 0.2, 0.2, 0.0); 

    
        // This gives transparency to transparent regions of pngs
    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    

    // Succesfully setup OpenGL Env
    return 0;
}
