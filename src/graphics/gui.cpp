
#include "graphics/utils.hpp"
#include "graphics/gui.hpp"
#include "ZR/core.hpp"

#include "glm/gtc/matrix_transform.hpp"



Gui::Gui(/* args */):exit_flag(false)
{
    setup_opengl();
    init_opengl();
}

Gui::~Gui()
{

}

int Gui::setup_opengl(){
    clear_color = Color(0.1, 0.2, 0.3);
    window_scale = 1.0;                                 //default scale of window
    window_height = 568;
    window_width = 568*1.61;

    // proj = glm::ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // This seems to be default(?)
    proj = glm::ortho(0.0, (double)window_width, 0.0, (double)window_height, -1.0, 1.0);
    view = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));

    return 0;
}

int Gui::init_opengl(){
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

    GLCALL(GLFWwindow *window = glfwCreateWindow(window_width, window_height, "OpenGL-CPP-Chess", NULL, NULL));

    if (!window){
        zr::log("Failed to create GLFW window.", zr::VERBOSITY_LEVEL::ERROR);
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gui_window = window;            // This code somehow needs to be at the end of the function.
    zr::log("Successfully created GLFW window.");

    // gui_window = window;

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

                                    // (Maybe so that whene window pops out of stack, only one instance of it's copy exists
                                    // but why would that matter?!)
        // This gives transparency to transparent regions of pngs
    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);

    return 0;
}