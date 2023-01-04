#ifndef __GAME_BOARD_HPP
#define __GAME_BOARD_HPP

#include "graphics/model.hpp"

#include "glm/glm.hpp"

#include <string>

typedef enum {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    InvalidPosition
} BoardPosition;
class GameBoard : public DrawableModel
{
public:
    const std::vector<std::string> pos_string = {
    "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1",
    "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",
    "A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3",
    "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4",
    "A5", "B5",  "C5", "D5", "E5", "F5", "G5", "H5",
    "A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6",
    "A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7",
    "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8",
    "Invalid(?)"
    };
    int board_width, board_height;
    int board_margin;
    int square_length;
    float window_to_board_ratio;

    inline std::string get_position_str(BoardPosition pos) const{
        return pos_string[pos];
    }
public:
    GameBoard(const std::string& shader_path, const std::string& texture_path);
    ~GameBoard();
    glm::vec3 get_translation_from_position(const std::string& chess_position) const;
    std::string get_board_position_str_from_xy(glm::vec2 board_xy) const;
    BoardPosition get_board_position_from_xy(glm::vec2 board_xy) const;
};



#endif //__GAME_BOARD_HPP
