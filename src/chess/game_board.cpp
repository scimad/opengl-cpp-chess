#include "chess/game_board.hpp"
#include "graphics/model.hpp"

#include "ZR/core.hpp"

GameBoard::GameBoard(const std::string& shader_path, const std::string& texture_path) : DrawableModel(shader_path, texture_path)
{
    //Setup board sides, board size, board colors and so on
    int initial_window_height = 568;

    window_to_board_ratio = (float) initial_window_height/ 568.0;

    board_width = 568 * window_to_board_ratio;
    board_height = 568 * window_to_board_ratio;

    board_margin = window_to_board_ratio * 20;
    square_length = window_to_board_ratio * 66;
}

GameBoard::~GameBoard()
{
}
