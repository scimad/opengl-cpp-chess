#include "chess/chess_piece.hpp"
#include "ZR/core.hpp"

ChessPiece::ChessPiece(const std::string& shader_path, const std::string& texture_path, ChessColors color, PieceType type, BoardPosition board_position)
    :   DrawableModel(shader_path, texture_path), state({board_position, color, type, ALIVE, true})
{

}

ChessPiece::~ChessPiece()
{
    zr::log("Chess piece freed from memory.", zr::VERBOSITY_LEVEL::DEBUG);
}
