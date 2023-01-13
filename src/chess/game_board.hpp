#ifndef __GAME_BOARD_HPP
#define __GAME_BOARD_HPP

#include "glm/glm.hpp"

#include "chess/common.hpp"
#include "graphics/model.hpp"
#include "ZR/core.hpp"

#include <string>

class GameBoard : public DrawableModel
{
    inline static const std::vector<std::string> pos_string = {
        "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1",
        "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",
        "A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3",
        "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4",
        "A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5",
        "A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6",
        "A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7",
        "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8",
        "Invalid"};

public:
    int board_width, board_height;
    int board_margin;
    int square_length;
    float window_to_board_ratio;

    static inline std::string get_position_str(BoardPosition pos)
    {
        if (pos > H8 || pos < A1)
            pos = InvalidPosition;
        return pos_string[pos];
    }

    static inline BoardFile get_file(BoardPosition pos)
    {
        return (BoardFile)(((int)pos) % 8 + 1);
    }

    static inline BoardFile get_left_file(BoardFile file)
    {
        if (file != A)
            return BoardFile ((int) file - 1);
        else
            return InvalidFile;
    }

    static inline BoardFile get_right_file(BoardPosition pos)
    {
        return (BoardFile)(((int)pos) % 8 + 1);
    }

    static inline BoardRank get_rank(BoardPosition pos)
    {
        return (BoardRank)(((int)pos) / 8 + 1);
    }

    static inline BoardPosition get_position(BoardFile file, BoardRank rank)
    {
        if ((int)file >= (int) BoardFile::A && (int)file <= (int) BoardFile::H && (int)rank >= 1 && (int)rank <= 8)
            return (BoardPosition)(((int)rank-1) * 8 + (file - 1));       //A1 is 0
        else
            return BoardPosition::InvalidPosition;
    }

    static inline BoardPosition get_position_from_str(std::string pos_str)
    {
        int index = 0;
        while (index <= 64)
        {
            if (pos_string[index] == pos_str)
            {
                return (BoardPosition)index;
            }
            ++index;
        }
        return InvalidPosition;
    }

    static BoardPosition get_position_on_right(BoardPosition from, ChessColors player_color, int n_steps = 1)
    {
        int direction = 1 - 2 * (int)player_color; // LIGHT moves in direction = 1, DARK moves in direction = -1
        return get_position((BoardFile)((int)GameBoard::get_file(from) + direction * n_steps), GameBoard::get_rank(from));
    }

    static BoardPosition get_position_on_left(BoardPosition from, ChessColors player_color, int n_steps = 1)
    {
        int direction = 1 - 2 * (int)player_color; // LIGHT moves in direction = 1, DARK moves in direction = -1
        return get_position((BoardFile)((int)GameBoard::get_file(from) - direction * n_steps), GameBoard::get_rank(from));
    }

    static BoardPosition get_position_on_front_left(BoardPosition from, ChessColors player_color, int n_steps = 1)
    {
        int direction = 1 - 2 * (int)player_color; // LIGHT moves in direction = 1, DARK moves in direction = -1
        return get_position((BoardFile)((int)GameBoard::get_file(from) - direction * n_steps), (BoardRank) ((int) GameBoard::get_rank(from) + direction * n_steps));
    }

    static BoardPosition get_position_on_front_right(BoardPosition from, ChessColors player_color, int n_steps = 1)
    {
        int direction = 1 - 2 * (int)player_color; // LIGHT moves in direction = 1, DARK moves in direction = -1
        return get_position((BoardFile)((int)GameBoard::get_file(from) + direction * n_steps), (BoardRank) ((int) GameBoard::get_rank(from) + direction * n_steps));
    }

    static BoardPosition get_position_on_back_left(BoardPosition from, ChessColors player_color, int n_steps = 1)
    {
        int direction = 1 - 2 * (int)player_color; // LIGHT moves in direction = 1, DARK moves in direction = -1
        return get_position((BoardFile)((int)GameBoard::get_file(from) - direction * n_steps), (BoardRank) ((int) GameBoard::get_rank(from) - direction * n_steps));
    }

    static BoardPosition get_position_on_back_right(BoardPosition from, ChessColors player_color, int n_steps = 1)
    {
        int direction = 1 - 2 * (int)player_color; // LIGHT moves in direction = 1, DARK moves in direction = -1
        return get_position((BoardFile)((int)GameBoard::get_file(from) + direction * n_steps), (BoardRank) ((int) GameBoard::get_rank(from) - direction * n_steps));
    }

    static BoardPosition get_position_ahead(BoardPosition from, ChessColors player_color, int n_steps = 1)
    {
        int direction = 1 - 2 * (int)player_color; // LIGHT moves in direction = 1, DARK moves in direction = -1
        return get_position(GameBoard::get_file(from), (BoardRank)((int)GameBoard::get_rank(from) + direction * n_steps));
    }

    static BoardPosition get_position_back(BoardPosition from, ChessColors player_color, int n_steps = 1)
    {
        int direction = 1 - 2 * (int)player_color; // LIGHT moves in direction = 1, DARK moves in direction = -1
        return get_position(GameBoard::get_file(from), (BoardRank)((int)GameBoard::get_rank(from) - direction * n_steps));
    }

public:
    GameBoard(const std::string &shader_path, const std::string &texture_path);
    ~GameBoard();
    glm::vec3 get_translation_from_position(const BoardPosition &position) const;
    std::string get_board_position_str_from_xy(glm::vec2 board_xy) const;
    BoardPosition get_board_position_from_xy(glm::vec2 board_xy) const;
};

#endif //__GAME_BOARD_HPP
