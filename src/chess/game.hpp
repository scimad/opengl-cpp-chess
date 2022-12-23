#ifndef __GAME_HPP
#define __GAME_HPP

#include "chess/game_board.hpp"
#include "chess/chess_piece.hpp"

#include "graphics/gui.hpp"

#include "glm/glm.hpp"

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
    glm::vec3 get_translation_from_position(std::string chess_position);

public:
    Gui gui;
    bool end_and_exit;
    
    std::vector<ChessPiece*> pieces;        // Can we do std::vector<ChessPiece> pieces; instead?
                                            // And where have I freed these objects? Am I leaking?
    GameBoard board;

    // ChessTimer timer;
    // GameHistory history;
    // bool can_castle[2]; //Can be indexed using LIGHT and DARK

public:
    ChessGame();
    ~ChessGame();
    void run();
    void update_gui();
    void processInput();


};

#endif// __GAME_HPP
