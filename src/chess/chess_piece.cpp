#include "chess/chess_piece.hpp"
#include "ZR/core.hpp"

ChessPiece::ChessPiece(const std::string& shader_path, const std::string& texture_path, ChessColors color, PieceType type, BoardPosition board_position)
    :   DrawableModel(shader_path, texture_path),
        color(color),
        type(type),
        position(board_position)
{

}

ChessPiece::~ChessPiece()
{
    zr::log("Chess piece freed from memory.", zr::VERBOSITY_LEVEL::DEBUG);
}
