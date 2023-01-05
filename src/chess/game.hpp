#ifndef __GAME_HPP
#define __GAME_HPP

#include "chess/game_board.hpp"
#include "chess/chess_piece.hpp"

#include "graphics/gui.hpp"

class GameState{
public:
    bool paused;
    bool is_checked;
    ChessColors current_player;
    bool is_white_castled;
    bool is_black_castled;
    unsigned int total_moves_count;
    unsigned int irreversible_moves_count;
    unsigned int repeated_moves_count;
    BoardPosition selected_position;
    BoardPosition move_from;
    BoardPosition move_to;
    GameState();
    ~GameState();
};

class ChessTimer{};
class GameHistory{};

class ChessGame{
private:
    const std::vector<std::string> color_names = { "LIGHT", "DARK" };
    inline std::string get_color_name(ChessColors chess_color){
        return color_names[chess_color];
    };
    ChessPiece* get_piece_at_position(BoardPosition position);

public:
    GLui glui;
    bool end_and_exit;
    
    std::vector<ChessPiece*> pieces;        // Can we do std::vector<ChessPiece> pieces; instead?
    GameBoard board;
    bool touch_to_move_rule;
    GameState game_state;
    bool is_legal_move(BoardPosition from, BoardPosition to){
        // TODO: WRITE LEGAL MOVE LOGIC
        return true;
    };
    void move(BoardPosition from, BoardPosition to);
    void capture(BoardPosition by, BoardPosition at);

    // ChessTimer timer;
    // GameHistory history;
    // bool can_castle[2]; //Can be indexed using LIGHT and DARK

public:
    ChessGame();
    ~ChessGame();
    void run();
    void process_requests();
};

#endif// __GAME_HPP
