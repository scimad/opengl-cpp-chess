#include "chess/chess_piece.hpp"
#include "ZR/core.hpp"

ChessPiece::ChessPiece(const std::string& shader_path, const std::string& texture_path, ChessColors color, PieceType type, BoardPosition board_position)
    :   DrawableModel(shader_path, texture_path),
        color(color),
        type(type),
        position(board_position),
        has_not_moved_yet(true)
{

}

ChessPiece::~ChessPiece()
{
    zr::log("Chess piece freed from memory.", zr::VERBOSITY_LEVEL::DEBUG);
}
