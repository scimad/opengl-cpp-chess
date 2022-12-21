#ifndef __GAME_HPP
#define __GAME_HPP

#include "chess/game_board.hpp"
#include "chess/pieces.hpp"

#include "graphics/opengl_env.hpp"
#include "graphics/gui.hpp"

class GameState{};
class ChessTimer{};
class GameHistory{};


enum{
    LIGHT = 0,
    DARK = 1
};

class ChessGame{
private:
    // ChessOpenGLEnv gui;

public:
    // bool exit_flag;
    // GameBoard board;
    // Pieces pieces;
    // ChessTimer timer;
    // GameHistory history;
    // bool can_castle[2]; //Can be indexed using LIGHT and DARK

    Gui gui;

    DrawableModel dqueen_model;//("../res/dark.shader", "../assets/Chess_qdt45.svg.png"); // ^3
    DrawableModel lrook_model;//("../res/light.shader", "../assets/Chess_rlt45.svg.png");
    DrawableModel dking_model;//("../res/dark.shader", "../assets/Chess_kdt45.svg.png");

public:
    ChessGame();
    // ChessGame(GameState current_state);
    ~ChessGame();
    void run();
    void processInput();

};

#endif// __GAME_HPP
