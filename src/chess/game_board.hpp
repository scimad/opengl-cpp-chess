#ifndef __GAME_BOARD_HPP
#define __GAME_BOARD_HPP

#include "interfaces/drawable.hpp"

class GameBoard : public Drawable
{
private:
public:
    GameBoard(/* args */);
    ~GameBoard();
    void setupStandard();

};




#endif //__GAME_BOARD_HPP
