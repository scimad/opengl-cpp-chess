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
    const std::vector<std::string> color_name = {"LIGHT", "DARK"};
public:
    ChessPiece(const std::string& shader_path, const std::string& texture_path, ChessColors color, PieceType type, BoardPosition board_position = InvalidPosition);
    BoardPosition position;
    ChessColors color;
    PieceType type;
    inline std::string get_color_str(){
        return color_name[(unsigned int) color];
    };
    inline std::string get_name_str(){
        return piece_name[(unsigned int) type];
    };

    ~ChessPiece();

};

#endif // __CHESS_PIECE_HPP
