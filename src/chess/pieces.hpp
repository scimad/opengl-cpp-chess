#ifndef __PIECES_HPP
#define __PIECES_HPP

#include "graphics/model.hpp"

#include <string>


class ChessPiece : DrawableModel{
public:
    ChessPiece(const std::string& shader_path, const std::string& texture_path, std::string board_position="");
};

#endif // __PIECES_HPP