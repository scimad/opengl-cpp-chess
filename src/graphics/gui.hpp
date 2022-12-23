#ifndef __GUI_HPP
#define __GUI_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/utils.hpp"
#include "graphics/renderer.hpp"

#include "chess/chess_piece.hpp"
#include "chess/game_board.hpp"

#include "glm/glm.hpp"

struct ChessGLConfig{

};

class Gui
{
private:
    int window_width;
    int window_height;

    float window_scale;    
    Color clear_color;
public:
    GLFWwindow* gui_window; // IMPORTANT: Remember how you use this pointer ^1
    Renderer renderer;
    bool exit_flag;

    // The following matrices perform the described transformation:
    // model        => 3D model's coordinate (in object's coordinate system) to world coordidnate system
    // view         => world coordinates to camera / view coordinate system
    // projection   => 3d coordinates of the camera coordinate system to 2D projection plane coordinates 
    // https://www.youtube.com/watch?v=-tonZsbHty8

    glm::mat4 proj, view; //, model matrix should go on somewhere and mvp should go somewhere;

    Gui(/* args */);
    ~Gui();
    int setup_opengl(); // setup opengl stuffs
    int init_opengl();  // init opengl stuffs
    int redraw_gl_contents(const std::vector<ChessPiece*>& pieces, const GameBoard& board);  //redraw opengl stuffs
};

#endif //__GUI_HPP
