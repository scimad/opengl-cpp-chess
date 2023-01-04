#include "graphics/gui.hpp"

#include "graphics/utils.hpp"
#include "chess/chess_piece.hpp"
#include "chess/game_board.hpp"

#include "chess/game.hpp"

#include "ZR/core.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"



GLui::GLui(/* args */):exit_flag(false)
{
    setup_opengl();
    init_opengl();
}

GLui::~GLui()
{

}

int GLui::setup_opengl(){
    clear_color = Color(0.1, 0.2, 0.3);
    window_scale = 1.0;                                 //default scale of window
    window_height = 568;
    window_width = 568 * glm::golden_ratio<float>();

    is_window_resizable = true;

    // proj = glm::ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // This seems to be default(?)
    proj = glm::ortho(0.0, (double)window_width, 0.0, (double)window_height, -1.0, 1.0);
    view = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));

    return 0;
}

GLui* GLui::get_gui_of_window(const GLFWwindow* window){
    int index = 0;  //at least one Chess GLui / Window exists in the program
    for (auto it = begin (all_window); it != end (all_window); ++it, ++index) {
         if (all_window[index] == window){
            return all_gui[index];
         }
    }
    return nullptr; //theoretically never happens.
}

void GLui::st_cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int index = 0;
    for (auto it = begin (all_window); it != end (all_window); ++it, ++index) {
         if (all_window[index] == window){
            (*(GLui*) all_gui[index]).cursor_xpos_wrt_window = xpos;
            (*(GLui*) all_gui[index]).cursor_ypos_wrt_window = ypos;
            (*(GLui*) all_gui[index]).cursor_position_callback();
            break;
         }
    }
}

void GLui::cursor_position_callback()
{


}

void GLui::st_window_resize_callback(GLFWwindow* window, int width, int height){
    int index = 0;
    for (auto it = begin (all_window); it != end (all_window); ++it, ++index) {
        if (all_window[index] == window){
            (*(GLui*) all_gui[index]).window_height = height;
            (*(GLui*) all_gui[index]).window_width = width;
            (*(GLui*) all_gui[index]).window_resize_callback();
            break;
        }
    }
}

void GLui::window_resize_callback(){
    // If anything needs to be done that window specific.
    // TODO: update the coordinate transformation matrix between window and board


    // if re-scaling is enabled, we need a scaling transformation as well

    // for no-scaling, only change of origin / axes is needed.








}

void GLui::st_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    int index = 0;
    for (auto it = begin (all_window); it != end (all_window); ++it, ++index) {
        if (all_window[index] == window){
            (*(GLui*) all_gui[index]).button = button;
            (*(GLui*) all_gui[index]).action = action;
            (*(GLui*) all_gui[index]).mods = mods;
            (*(GLui*) all_gui[index]).mouse_button_callback();
            break;
        }
    }
}

void GLui::mouse_button_callback()
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        // zr::log("Left Button clicked at: " + std::to_string(cursor_xpos_wrt_window) + ", " + std::to_string(cursor_ypos_wrt_window));
        glm::vec2 window_xy((float) cursor_xpos_wrt_window, (float) cursor_ypos_wrt_window);
        button_actions_queue.push_back(std::tie<int, glm::vec2>(action, window_xy));
        m_event.action = action;
        m_event.button = button;
        m_event.x = cursor_xpos_wrt_window;
        m_event.y = cursor_ypos_wrt_window;
    }
}

glm::vec2 GLui::transform_xy_window_to_board(const GameBoard& board, glm::vec2 window_xy){

    // board_xy = MATMUL (window_to_board_transformation, window_xy)
    window_to_board_transformation[0][0] = 1;
    window_to_board_transformation[0][1] = - board.board_margin;

    window_to_board_transformation[1][0] = -1;
    window_to_board_transformation[1][1] = window_height - board.board_margin;

    zr::log("window x,y = " + std::to_string(window_xy.x) + ", " + std::to_string(window_xy.y), zr::VERBOSITY_LEVEL::DEBUG);
    glm::vec2 board_xy = glm::vec2(
        (float) (window_to_board_transformation[0][0] * window_xy.x + window_to_board_transformation[0][1]),
        (float) (window_to_board_transformation[1][0] * window_xy.y + window_to_board_transformation[1][1])
    );
    return board_xy;
};



int GLui::init_opengl(){
    if (!glfwInit()){
        zr::log("GLFW initialization failed.", zr::VERBOSITY_LEVEL::ERROR);
        return -1;
    }
    zr::log("Successfully initialized GLFW.", zr::VERBOSITY_LEVEL::DEBUG);

    if (!is_window_resizable){
        GLCALL(glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE));
    }else{
        GLCALL(glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE));
    }

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
    zr::log("Successfully created GLFW window.", zr::VERBOSITY_LEVEL::INFO);

    // gui_window = window;

        // glfwSwapInterval(1);

    // Initialize GLEW
    GLenum err = glewInit();                      //Must do after glfwMakeContextCurrent() or alternatively after properly initializing GLUT
    if (GLEW_OK != err){
        zr::log("Failed to initialize GLEW. Err: " + std::string((const char*)(glewGetErrorString(err))), zr::VERBOSITY_LEVEL::ERROR);
        glfwTerminate();
        return -1;
    }
    zr::log("Successfully initialized GLEW.", zr::VERBOSITY_LEVEL::DEBUG);
    zr::log("OpenGL Version: " + std::string((const char*) glGetString(GL_VERSION)), zr::VERBOSITY_LEVEL::INFO);

    // This gives transparency to transparent regions of pngs
    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);

    glfwSetMouseButtonCallback(window, st_mouse_button_callback);
    glfwSetCursorPosCallback(window, st_cursor_position_callback);
    glfwSetWindowSizeCallback(window, st_window_resize_callback);

    GLui::all_gui.push_back(this);
    GLui::all_window.push_back(window);

    return 0;
}

int GLui::redraw_gl_contents(const std::vector<ChessPiece*>& pieces, const GameBoard& board){
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