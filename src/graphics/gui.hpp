#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "utils.hpp"
#include "glm/glm.hpp"

class Gui
{
private:
    int window_width;
    int window_height;

    float window_scale;    
    Color clear_color;
public:
    GLFWwindow* gui_window;

    // The following matrices perform the described transformation:
    // model        => 3D model's coordinate (in object's coordinate system) to world coordidnate system
    // view         => world coordinates to camera / view coordinate system
    // projection   => 3d coordinates of the camera coordinate system to 2D projection plane coordinates 
    // https://www.youtube.com/watch?v=-tonZsbHty8

    glm::mat4 proj, view; //, model matrix should go on somewhere and mvp should go somewhere;

    Gui(/* args */);
    ~Gui();
    int setup_opengl();
    int init_opengl();
};
