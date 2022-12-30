#include "chess/game_board.hpp"
#include "graphics/model.hpp"

#include "glm/glm.hpp"

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

glm::vec3 GameBoard::get_translation_from_position(const std::string& chess_position) const {
    glm::vec3 center_of_A1(
                (float) board_margin + (float) square_length/2.0,
                (float) board_margin + (float) square_length/2.0,
                0);
    char file = chess_position.c_str()[0];  //Assuming uppercase
    char rank = chess_position.c_str()[1];

    glm::vec3 position = center_of_A1 + glm::vec3(
        ((int) file - (int) 'A') * (float) square_length,        // ASCII of 'A' is 65
        ((int) rank - (int) '1') * (float) square_length,        // ASCII of '1' is 49
        0);
    return position;
}

std::string GameBoard::get_board_position_from_xy(glm::vec2 board_xy) const {
    double x_pos_wrt_board = board_xy.x;
    double y_pos_wrt_board = board_xy.y;
    std::string position = "";
    zr::log("Board x, board y  = " + std::to_string(x_pos_wrt_board) + ", "+ std::to_string(y_pos_wrt_board));
    if (x_pos_wrt_board >= 0 && x_pos_wrt_board < 8 * square_length && y_pos_wrt_board >= 0 && y_pos_wrt_board <  8 * square_length){
        char file = (char)((int)(x_pos_wrt_board / (double) square_length) + 65);         // ASCII of 'A' is 65
        int rank = (int)(y_pos_wrt_board / (double) square_length) + 1;
        position = std::string(1, file) +std::to_string(rank);
    }
    return position;
}
