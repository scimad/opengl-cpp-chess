#ifndef __GAME_BOARD_HPP
#define __GAME_BOARD_HPP

#include "interfaces/drawable.hpp"
#include <string>

class GameBoard : public Drawable
{
public:
    int width_ratio, height_ratio;
    int margin_ratio;
    int square_length_ratio;
private:
    std::string board_image;
public:
    GameBoard(/* args */);
    ~GameBoard();
    void setupStandard();
};




#endif //__GAME_BOARD_HPP
