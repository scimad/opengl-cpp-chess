#ifndef __CHESS_PIECE_HPP
#define __CHESS_PIECE_HPP

#include "graphics/model.hpp"

#include <string>

class ChessPiece : public DrawableModel{
public:
    ChessPiece(const std::string& shader_path, const std::string& texture_path, std::string board_position="");
    std::string position;
};

#endif // __CHESS_PIECE_HPP
