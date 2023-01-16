
#ifndef __GAME_HPP
#define __GAME_HPP

#include "chess/common.hpp"
#include "chess/game_state.hpp"
#include "chess/game_board.hpp"
#include "chess/chess_piece.hpp"

#include "graphics/gui.hpp"

#include <stack>

class ChessGame{
private:
    const std::vector<std::string> color_names = { "LIGHT", "DARK" };
    inline std::string get_color_name(ChessColors chess_color){
        return color_names[chess_color];
    };
    ChessPiece* get_piece_at_position(BoardPosition position);
    bool does_this_move_leave_me_in_check(ChessMove move);
    bool is_check_for(ChessColors player);

public:
    GLui glui;
    bool end_and_exit;
    
    std::vector<ChessPiece*> pieces;        // Can we do std::vector<ChessPiece> pieces; instead?
    GameBoard board;
    DrawableModel square;
    bool touch_to_move_rule;
    GameState game_state;
    ChessMove is_legal_move(BoardPosition from, BoardPosition to);
    void make_move(ChessMove requested_move, bool is_real_move=true);
    // void capture(ChessMove capturing_move);
    std::vector<ChessMove> get_raw_valid_moves(BoardPosition position);
    std::vector<ChessMove> get_valid_moves(BoardPosition position, bool check_for_checks = true);
    std::stack<ChessMove> moves;
    // ChessTimer timer;
    // bool can_castle[2]; //Can be indexed using LIGHT and DARK

public:
    ChessGame();
    ~ChessGame();
    void run();
    void process_requests();
};

#endif// __GAME_HPP
