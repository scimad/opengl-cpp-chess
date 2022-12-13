#ifndef __GAME_HPP
#define __GAME_HPP

#include "chess/game_board.hpp"
#include "graphics/opengl_env.hpp"

class GameState{};
class Pieces{
public:
    void setupStandard(){};

};
class ChessTimer{};
class GameHistory{};


enum{
    LIGHT = 0,
    DARK = 1
};

class ChessGame{
private:
    ChessOpenGLEnv gl_env;

public:
    bool exit_flag;
    GameBoard board;
    Pieces pieces;
    ChessTimer timer;
    GameHistory history;
    bool can_castle[2]; //Can be indexed using LIGHT and DARK

public:
    ChessGame();
    ChessGame(GameState current_state);
    ~ChessGame();
    void run();

};

#endif// __GAME_HPP
