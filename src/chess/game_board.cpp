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

void GameBoard::setupStandard(){

    // apparently dynamically modifying vertex buffer and rebinding it isn't working
    // so, for now, the chess board is being fixed by using a different mvp, which
    // may also be the better way to do things.

    // vertex_data[0] = (float) margin_ratio;
    // vertex_data[1] = (float) margin_ratio;
    // vertex_data[4] = (boardboard_width;
    // vertex_data[5] = (float) margin_ratio;
    // vertex_data[8] = (boardboard_width;
    // vertex_data[9] = (float) board_height;
    // vertex_data[12] = (float) margin_ratio;
    // vertex_data[13] = (float) board_height;
}