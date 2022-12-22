#ifndef __GAME_HPP
#define __GAME_HPP

#include "chess/game_board.hpp"
#include "chess/pieces.hpp"

#include "graphics/opengl_env.hpp"
#include "graphics/gui.hpp"

enum ChessColors{
    LIGHT = 0,
    DARK = 1
};

typedef ChessColors Player;

class GameState{
    bool is_checked;
    Player current_player;
    bool is_white_castled;
    bool is_black_castled;
    unsigned int irreversible_move_count;
    unsigned int repeated_moves_count;
};

class ChessTimer{};
class GameHistory{};

class ChessGame{
private:
    // ChessOpenGLEnv gui;
    GameState current_state;

public:
    bool exit_flag;
    
    // Pieces pieces;
    // ChessTimer timer;
    // GameHistory history;
    // bool can_castle[2]; //Can be indexed using LIGHT and DARK

    Gui gui;

    // DrawableModels:
    GameBoard board;

    //Convert these to ChessPiece class objects (that inherit DrawableModel)
    DrawableModel dqueen_model;
    DrawableModel lrook_model;
    DrawableModel dking_model;

public:
    ChessGame();
    ~ChessGame();
    void run();
    void processInput();

};

#endif// __GAME_HPP
