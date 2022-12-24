#include "game.hpp"
#include "ZR/core.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include<string>
#include<memory>

ChessGame::ChessGame():
    board("../res/basic.shader", "../assets/Board.png"),end_and_exit(false)
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
    for (auto& piece : pieces){
        delete piece;
    }
}

void ChessGame::processInput() {
    glfwPollEvents();
    if (glfwGetKey(gui.gui_window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(gui.gui_window, true);
    }

    gui.exit_flag = glfwWindowShouldClose(gui.gui_window);
}

void ChessGame::run(){
    // Utility variables

    /* Loop until the user closes the window */
    while (!gui.exit_flag || (*this).end_and_exit){
        processInput();
        gui.redraw_gl_contents(pieces, board);
    }

    glfwTerminate(); // Refer to the notes on README.md of this project
}
