#include "chess/chess_piece.hpp"
#include "ZR/core.hpp"

ChessPiece::ChessPiece(const std::string& shader_path, const std::string& texture_path, std::string board_position)
    :   DrawableModel(shader_path, texture_path),
        position(board_position)
{

}

ChessPiece::~ChessPiece()
{
    zr::log("Chess piece freed from memory");
}
