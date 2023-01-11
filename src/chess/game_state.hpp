
#ifndef __GAME_STATE_HPP
#define __GAME_STATE_HPP

#include "chess/common.hpp"
#include "chess/game_board.hpp"
#include "chess/chess_piece.hpp"

class GameState{
public:
    bool paused;
    bool is_checked;
    ChessColors current_player, opponent_player;
    bool is_white_castled;
    bool is_black_castled;
    unsigned int total_moves_count;
    unsigned int irreversible_moves_count;
    unsigned int repeated_moves_count;
    BoardPosition selected_position;
    BoardPosition move_from;
    BoardPosition move_to;
    const ChessPiece* last_moved_piece;
    std::vector<ChessMove> possible_moves;
    GameState();
    ~GameState();
};

#endif// __GAME_STATE_HPP
