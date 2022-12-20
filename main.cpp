#include "chess/game.hpp"

#include "graphics/gui.hpp"
#include "graphics/model.hpp"

#include <memory>

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main(){

    GLFWwindow* window;
    Gui gui;
    
    //IMPORTANT: Remember how you use this pointer ^1
    window = gui.gui_window;

    DrawableModel dqueen_model("../res/dark.shader", "../assets/Chess_qdt45.svg.png"); // ^3
    DrawableModel lrook_model("../res/light.shader", "../assets/Chess_rlt45.svg.png");
    DrawableModel dking_model("../res/dark.shader", "../assets/Chess_kdt45.svg.png");

    glm::mat4 model = glm::mat4(1.0);
    // glm::mat4 mvp = proj * view * model;

    Renderer renderer;

    // Utility variables
    static bool exit_flag = false;
    float r = 0.0f;
    float increament = 0.0025f;

    /* Loop until the user closes the window */
    while (!exit_flag){
        r += increament;
        if (r > 0.25 || r < 0) increament *= -1;
        exit_flag = glfwWindowShouldClose(window);
        processInput(window);
        /* Render here */
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(300, 300, 0) + glm::vec3(100, 100, 0));
            glm::mat4 mvp = gui.proj * gui.view * model;
            // Following shader binding is actually refactored / solved using Materials
            (*dqueen_model.shader_ptr).bind();
            // shader.setUniform1i("u_texture", 0);
            (*dqueen_model.shader_ptr).setUniformMat4f("u_MVP", mvp);
            (*dqueen_model.shader_ptr).setUniform4f("u_color", r, 0, 0, 0.0); //if uniform is not used in shader, it gives error / notification
            renderer.draw(dqueen_model);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(300, 300, 0) + glm::vec3(200, 200, 0));
            glm::mat4 mvp = gui.proj * gui.view * model;

            (*lrook_model.shader_ptr).bind();
            // shader.setUniform1i("u_texture", 0);
            (*lrook_model.shader_ptr).setUniformMat4f("u_MVP", mvp);
            (*lrook_model.shader_ptr).setUniform4f("u_color", r, 0, 0, 0.0); //if uniform is not used in shader, it gives error / notification
            renderer.draw(lrook_model);
        }


        {
            glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(450, 300, 0) + glm::vec3(100, 100, 0));
            glm::mat4 mvp = gui.proj * gui.view * model;
           // Following shader binding is actually refactored / solved using Materials
            (*dking_model.shader_ptr).bind();
            // shader.setUniform1i("u_texture", 0);
            (*dking_model.shader_ptr).setUniformMat4f("u_MVP", mvp);
            (*dking_model.shader_ptr).setUniform4f("u_color", r, 0, 0, 0.0); //if uniform is not used in shader, it gives error / notification
            renderer.draw(dking_model);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        renderer.clear();
        glfwPollEvents();
    }

    glfwTerminate(); // Refer to the notes on README.md of this project   
    return 0;
}
