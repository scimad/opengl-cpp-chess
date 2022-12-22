#ifndef __GAME_BOARD_HPP
#define __GAME_BOARD_HPP

#include "graphics/model.hpp"

#include <string>

class GameBoard : public DrawableModel
{
public:
    int width_ratio, height_ratio;
    int margin_ratio;
    int square_length_ratio;
private:
    std::string board_image;
public:
    GameBoard(const std::string& shader_path, const std::string& texture_path);
    ~GameBoard();
    void setupStandard();
};




#endif //__GAME_BOARD_HPP
