#ifndef __GAME_HPP
#define __GAME_HPP

#include "chess/game_board.hpp"

class GameState{};
class Pieces{
public:
    void setupStandard(){};

};
class ChessTimer{};
class GameHistory{};

class ChessOpenGLEnv{};

enum{
    LIGHT = 0,
    DARK = 1
};

class ChessGame{
private:
    ChessOpenGLEnv gl_env;

    GameBoard board;
    Pieces pieces;
    ChessTimer timer;
    GameHistory history;

    bool can_castle[2]; //Can be indexed using LIGHT and DARK

public:
    ChessGame();
    ChessGame(GameState current_state);


    ~ChessGame();

    
};

#endif// __GAME_HPP
