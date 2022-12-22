#ifndef __GAME_BOARD_HPP
#define __GAME_BOARD_HPP

#include "graphics/model.hpp"

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
};




#endif //__GAME_BOARD_HPP
