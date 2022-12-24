#include "graphics/gui.hpp"

#include "graphics/utils.hpp"
#include "chess/chess_piece.hpp"
#include "chess/game_board.hpp"

#include "chess/game.hpp"

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

void Gui::st_cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int index = 0;
    for (auto it = begin (all_window); it != end (all_window); ++it, ++index) {
         if (all_window[index] == window){
            (*(Gui*) all_gui[index]).cursor_xpos = xpos;
            (*(Gui*) all_gui[index]).cursor_ypos = ypos;
            (*(Gui*) all_gui[index]).cursor_position_callback();
            break;
         }
    }
}


void Gui::cursor_position_callback()
{


}

void Gui::mouse_button_callback()
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        zr::log("Left Button clicked");
    }
}


void Gui::st_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    int index = 0;
    for (auto it = begin (all_window); it != end (all_window); ++it, ++index) {
        if (all_window[index] == window){
            (*(Gui*) all_gui[index]).button = button;
            (*(Gui*) all_gui[index]).action = action;
            (*(Gui*) all_gui[index]).mods = mods;
            (*(Gui*) all_gui[index]).mouse_button_callback();
            break;
        }
    }
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

    glfwSetMouseButtonCallback(window, st_mouse_button_callback);
    glfwSetCursorPosCallback(window, st_cursor_position_callback);

    Gui::all_gui.push_back(this);
    Gui::all_window.push_back(window);

    return 0;
}

int Gui::redraw_gl_contents(const std::vector<ChessPiece*>& pieces, const GameBoard& board){
        /* Render here || Make the draw calls here || Draw the models here*/
    // Render board
    {
        glm::mat4 model = glm::scale(glm::mat4(1.0), glm::vec3((float) board.board_width / (float) board.square_length));
        glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3((float) board.board_width/2.0, (float) board.board_height/2.0, 0.0));
        glm::mat4 mvp = proj * view * model;

        // Binding is handled inside setUniform
        // shader.setUniform1i("u_texture", 0);
        (*board.shader_ptr).setUniformMat4f("u_MVP", mvp);
        (*board.shader_ptr).setUniform4f("u_color", 0.2, 0.3, 0.4, 0.0); //if uniform is not used in shader, it gives error / notification
        renderer.draw(board);
    }

    //Render pieces
    {
        for (auto& piece : pieces){
            glm::mat4 model = glm::translate(glm::mat4(1.0),  board.get_translation_from_position((*piece).position));
            glm::mat4 mvp = proj * view * model;

            // Binding is handled inside setUniform
            // shader.setUniform1i("u_texture", 0);
            (*(*piece).shader_ptr).setUniformMat4f("u_MVP", mvp);
            (*(*piece).shader_ptr).setUniform4f("u_color", 0.2, 0.3, 0.4, 0.0); //if uniform is not used in shader, it gives error / notification
            renderer.draw((*piece));
        }
    }

    //Render anything else
    {

    }

    /* Swap front and back buffers */
    glfwSwapBuffers(gui_window);
    renderer.clear();
    return 0;
}