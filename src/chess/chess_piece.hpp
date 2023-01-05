#ifndef __CHESS_PIECE_HPP
#define __CHESS_PIECE_HPP

#include "graphics/model.hpp"

#include "chess/game_board.hpp"

class ChessPiece : public DrawableModel{
public:
    ChessPiece(const std::string& shader_path, const std::string& texture_path, BoardPosition board_position = InvalidPosition);
    BoardPosition position;

    ~ChessPiece();

};

#endif // __CHESS_PIECE_HPP
