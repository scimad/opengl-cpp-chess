#include "game.hpp"
#include "ZR/core.hpp"

ChessGame::ChessGame():
    dqueen_model("../res/dark.shader", "../assets/Chess_qdt45.svg.png"),
    lrook_model("../res/light.shader", "../assets/Chess_rlt45.svg.png"),
    dking_model("../res/dark.shader", "../assets/Chess_kdt45.svg.png")
{
    // board.setupStandard();
    // pieces.setupStandard();
    // gui.initialize(board, pieces, 1.5);
}

// ChessGame::ChessGame(GameState current_state){

// }

ChessGame::~ChessGame(){

}

void ChessGame::processInput() {
    if (glfwGetKey(gui.gui_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(gui.gui_window, true);
}

void ChessGame::run(){
    // Utility variables
    static bool exit_flag = false;
    float r = 0.0f;
    float increament = 0.0025f;

    /* Loop until the user closes the window */
    while (!exit_flag){
        r += increament;
        if (r > 0.25 || r < 0) increament *= -1;
        exit_flag = glfwWindowShouldClose(gui.gui_window);
        processInput();
        /* Render here || Make the draw calls here || Draw the models here*/
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(300, 300, 0) + glm::vec3(100, 100, 0));
            glm::mat4 mvp = gui.proj * gui.view * model;
            // Following shader binding is actually refactored / solved using Materials
            (*dqueen_model.shader_ptr).bind();
            // shader.setUniform1i("u_texture", 0);
            (*dqueen_model.shader_ptr).setUniformMat4f("u_MVP", mvp);
            (*dqueen_model.shader_ptr).setUniform4f("u_color", r, 0, 0, 0.0); //if uniform is not used in shader, it gives error / notification
            gui.renderer.draw(dqueen_model);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(300, 300, 0) + glm::vec3(200, 200, 0));
            glm::mat4 mvp = gui.proj * gui.view * model;

            (*lrook_model.shader_ptr).bind();
            // shader.setUniform1i("u_texture", 0);
            (*lrook_model.shader_ptr).setUniformMat4f("u_MVP", mvp);
            (*lrook_model.shader_ptr).setUniform4f("u_color", r, 0, 0, 0.0); //if uniform is not used in shader, it gives error / notification
            gui.renderer.draw(lrook_model);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(450, 300, 0) + glm::vec3(100, 100, 0));
            glm::mat4 mvp = gui.proj * gui.view * model;
           // Following shader binding is actually refactored / solved using Materials
            (*dking_model.shader_ptr).bind();
            // shader.setUniform1i("u_texture", 0);
            (*dking_model.shader_ptr).setUniformMat4f("u_MVP", mvp);
            (*dking_model.shader_ptr).setUniform4f("u_color", r, 0, 0, 0.0); //if uniform is not used in shader, it gives error / notification
            gui.renderer.draw(dking_model);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(gui.gui_window);
        gui.renderer.clear();
        glfwPollEvents();
    }

    glfwTerminate(); // Refer to the notes on README.md of this project
}
