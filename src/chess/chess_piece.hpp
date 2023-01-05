#ifndef __CHESS_PIECE_HPP
#define __CHESS_PIECE_HPP

#include "graphics/model.hpp"

#include "chess/game_board.hpp"

typedef enum {
    LIGHT = 0,
    DARK = 1
} ChessColors;

typedef enum {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING    
} PieceType;


class ChessPiece : public DrawableModel{
private:
    const std::vector<std::string> piece_name = {"PAWN", "ROOK", "KNIGHT", "BISHOP", "QUEEN", "KING"};
public:
    ChessPiece(const std::string& shader_path, const std::string& texture_path, BoardPosition board_position = InvalidPosition);
    BoardPosition position;
    ChessColors color;
    inline std::string get_name_by_piece(PieceType piece){
        return piece_name[(unsigned int) piece];
    };

    ~ChessPiece();

};

#endif // __CHESS_PIECE_HPP
