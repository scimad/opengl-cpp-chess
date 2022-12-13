#include "game.hpp"

ChessGame::ChessGame(){
    board.setupStandard();
    pieces.setupStandard();
}

ChessGame::ChessGame(GameState current_state){

}

ChessGame::~ChessGame(){

}

void ChessGame::run(){
    //This will be game's main loop
    /* Loop until the user closes the window */
    while (!exit_flag){
        exit_flag = gl_env.refresh_window();
    }

}
