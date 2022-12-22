#include "game.hpp"
#include "ZR/core.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include<string>
#include<memory>

ChessGame::ChessGame():
    board("../res/basic.shader", "../assets/Board.png")
{
    //8 light pawns and 8 dark pawns
    for (size_t i=0; i< 8; i++)
    {
        pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_plt45.svg.png", std::string({char(65+i), '2'})));
        pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_pdt45.svg.png", std::string({char(65+i), '7'})));
    }

    //light Queen and dark Queen
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_qlt45.svg.png", "D1"));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_qdt45.svg.png", "D8"));

    //light Kind and dark King
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_klt45.svg.png", "E1"));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_kdt45.svg.png", "E8"));

    //2 light bishops and 2 dark bishops
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_blt45.svg.png", "C1"));
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_blt45.svg.png", "F1"));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_bdt45.svg.png", "C8"));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_bdt45.svg.png", "F8"));

    //2 light knights and 2 dark knights
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_nlt45.svg.png", "B1"));
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_nlt45.svg.png", "G1"));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_ndt45.svg.png", "B8"));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_ndt45.svg.png", "G8"));

    //2 light rooks and 2 dark rooks
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_rlt45.svg.png", "A1"));
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_rlt45.svg.png", "H1"));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_rdt45.svg.png", "A8"));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_rdt45.svg.png", "H8"));

}

// ChessGame::ChessGame(GameState current_state){

// }

ChessGame::~ChessGame(){

}

void ChessGame::processInput() {
    if (glfwGetKey(gui.gui_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(gui.gui_window, true);
}

glm::vec3 ChessGame::get_translation_from_position(std::string chess_position){
    glm::vec3 center_of_A1(
                (float) board.board_margin + (float) board.square_length/2.0,
                (float) board.board_margin + (float) board.square_length/2.0,
                0);
    char file = chess_position.c_str()[0];  //Assuming uppercase
    char rank = chess_position.c_str()[1];

    glm::vec3 position = center_of_A1 + glm::vec3(
        ((int) file - 65) * (float) board.square_length,        // ASCII of 'A' is 65
        ((int) rank - 49) * (float) board.square_length,        // ASCII of '1' is 49
        0);
    return position;
}

void ChessGame::run(){
    // Utility variables
    exit_flag = false;
    float r = 0.0f;
    float increament = 0.0025f;
    /* Loop until the user closes the window */
    while (!exit_flag){
        r += increament;
        if (r > 0.25 || r < 0) increament *= -1;
        exit_flag = glfwWindowShouldClose(gui.gui_window);
        processInput();
        /* Render here || Make the draw calls here || Draw the models here*/

        // Render board
        {
            glm::mat4 model = glm::scale(glm::mat4(1.0), glm::vec3((float) board.board_width / (float) board.square_length));
            glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3((float) board.board_width/2.0, (float) board.board_height/2.0, 0.0));
            glm::mat4 mvp = gui.proj * view * model;
           // Following shader binding is actually refactored / solved using Materials
            (*board.shader_ptr).bind();
            // shader.setUniform1i("u_texture", 0);
            (*board.shader_ptr).setUniformMat4f("u_MVP", mvp);
            (*board.shader_ptr).setUniform4f("u_color", r/2, r/4, 0, 0.0); //if uniform is not used in shader, it gives error / notification
            gui.renderer.draw(board);
        }

        //Render pieces
        {
            for (auto& piece : pieces){
                glm::mat4 model = glm::translate(glm::mat4(1.0), get_translation_from_position((*piece).position));
                glm::mat4 mvp = gui.proj * gui.view * model;
                // Following shader binding is actually refactored / solved using Materials
                (*(*piece).shader_ptr).bind();
                // shader.setUniform1i("u_texture", 0);
                (*(*piece).shader_ptr).setUniformMat4f("u_MVP", mvp);
                (*(*piece).shader_ptr).setUniform4f("u_color", r, 0, 0, 0.0); //if uniform is not used in shader, it gives error / notification
                gui.renderer.draw((*piece));
            }
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(gui.gui_window);
        gui.renderer.clear();
        glfwPollEvents();
    }

    glfwTerminate(); // Refer to the notes on README.md of this project
}
