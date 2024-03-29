#ifndef __CHESS_PIECE_HPP
#define __CHESS_PIECE_HPP

#include "graphics/model.hpp"

#include "chess/game_board.hpp"
#include "chess/common.hpp"

typedef enum {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
} PieceType;

typedef enum {
    ALIVE,
    DEAD
} LifeStatus;


struct PieceState{
    BoardPosition position;
    ChessColors color;
    PieceType type;
    LifeStatus status;
    bool has_not_moved_yet;
};

class ChessPiece : public DrawableModel{
private:
    inline static const std::vector<std::string> piece_name = {"PAWN", "ROOK", "KNIGHT", "BISHOP", "QUEEN", "KING"};
    inline static const std::vector<std::string> color_name = {"LIGHT", "DARK"};
public:
    ChessPiece(const std::string& shader_path, const std::string& texture_path, ChessColors color, PieceType type, BoardPosition board_position = InvalidPosition);
    PieceState state;

    BoardPosition& position = state.position;
    ChessColors& color = state.color;
    PieceType& type = state.type;
    LifeStatus& status = state.status;
    bool& has_not_moved_yet = state.has_not_moved_yet;

    inline std::string get_color_str(){
        return color_name[(unsigned int) state.color];
    };
    inline std::string get_name_str(){
        return piece_name[(unsigned int) state.type];
    };

    ~ChessPiece();

};

// class PawnPiece : public ChessPiece {
// public:
//     PawnPiece();
//     ~PawnPiece();
// };

// class RookPiece : public ChessPiece {
// public:
//     RookPiece();
//     ~RookPiece();
// };

// class KnightPiece : public ChessPiece {
// public:
//     KnightPiece();
//     ~KnightPiece();
// };

// class BishopPiece : public ChessPiece {
// public:
//     BishopPiece();
//     ~BishopPiece();
// };

// class QueenPiece : public ChessPiece {
// public:
//     QueenPiece();
//     ~QueenPiece();
// };

// class KingPiece : public ChessPiece {
// public:
//     KingPiece();
//     ~KingPiece();
// };

#endif // __CHESS_PIECE_HPP
