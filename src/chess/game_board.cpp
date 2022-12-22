#include "chess/game_board.hpp"
#include "graphics/model.hpp"

#include "ZR/core.hpp"

GameBoard::GameBoard(const std::string& shader_path, const std::string& texture_path) : DrawableModel(shader_path, texture_path)
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

    // vertex_data[0] = (float) margin_ratio;
    // vertex_data[1] = (float) margin_ratio;
    // vertex_data[4] = (float) width_ratio;
    // vertex_data[5] = (float) margin_ratio;
    // vertex_data[8] = (float) width_ratio;
    // vertex_data[9] = (float) height_ratio;
    // vertex_data[12] = (float) margin_ratio;
    // vertex_data[13] = (float) height_ratio;
}