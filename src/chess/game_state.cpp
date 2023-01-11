
#include "chess/game_state.hpp"

#include "chess/common.hpp"
#include "chess/game_board.hpp"
#include "chess/chess_piece.hpp"


GameState::GameState() :
    paused(true),
    current_player(ChessColors::LIGHT),
    opponent_player(ChessColors::DARK),
    selected_position(BoardPosition::InvalidPosition),
    total_moves_count(0),
    irreversible_moves_count(0),
    repeated_moves_count(0),
    is_checked(false),
    is_white_castled(false),
    is_black_castled(false),
    move_from(BoardPosition::InvalidPosition),
    move_to(BoardPosition::InvalidPosition),
    last_moved_piece(nullptr)
{
    zr::log("New game started.", zr::INFO);
}

GameState::~GameState()
{
}
