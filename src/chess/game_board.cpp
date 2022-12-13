#include "chess/game_board.hpp"

GameBoard::GameBoard()
{
}

GameBoard::~GameBoard()
{
}

void GameBoard::setupStandard(){
	//Setup board sides, board size, board colors and so on
	width_ratio = 568;
	height_ratio = 568;
	margin_ratio = 20;
	square_length_ratio = 66;
}