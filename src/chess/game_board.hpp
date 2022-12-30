#ifndef __GAME_BOARD_HPP
#define __GAME_BOARD_HPP

#include "graphics/model.hpp"

#include "glm/glm.hpp"

#include <string>

class GameBoard : public DrawableModel
{
public:
    int board_width, board_height;
    int board_margin;
    int square_length;

    float window_to_board_ratio;
public:
    GameBoard(const std::string& shader_path, const std::string& texture_path);
    ~GameBoard();
    glm::vec3 get_translation_from_position(const std::string& chess_position) const;
    std::string get_board_position_from_xy(glm::vec2 board_xy) const;
};



#endif //__GAME_BOARD_HPP
