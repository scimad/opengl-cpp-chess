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

glm::vec3 GameBoard::get_translation_from_position(const BoardPosition& position) const {
    // TODO: We can return this without using string operations
    // TODO: Completely remove string based positionining system
    std::string chess_position = get_position_str(position);
    glm::vec3 center_of_A1(
                (float) board_margin + (float) square_length/2.0,
                (float) board_margin + (float) square_length/2.0,
                0);
    char file = chess_position.c_str()[0];  //Assuming uppercase
    char rank = chess_position.c_str()[1];

    glm::vec3 t_vec = center_of_A1 + glm::vec3(
        ((int) file - (int) 'A') * (float) square_length,        // ASCII of 'A' is 65
        ((int) rank - (int) '1') * (float) square_length,        // ASCII of '1' is 49
        0);
    return t_vec;
}

std::string GameBoard::get_board_position_str_from_xy(glm::vec2 board_xy) const {
    BoardPosition position = get_board_position_from_xy(board_xy);
    return get_position_str(position);
}

BoardPosition GameBoard::get_board_position_from_xy(glm::vec2 board_xy) const {
    double x_pos_wrt_board = board_xy.x;
    double y_pos_wrt_board = board_xy.y;
    BoardPosition position = BoardPosition::InvalidPosition;
    zr::log("x, y (with respect to board)  = " + std::to_string(x_pos_wrt_board) + ", "+ std::to_string(y_pos_wrt_board), zr::VERBOSITY_LEVEL::DEBUG);
    if (x_pos_wrt_board >= 0 && x_pos_wrt_board < 8 * square_length && y_pos_wrt_board >= 0 && y_pos_wrt_board <  8 * square_length){
        int file_num = (int)(x_pos_wrt_board / (double) square_length);         // 'A' file is 1
        int rank_num = (int)(y_pos_wrt_board / (double) square_length);             //  1 rank is 1
        position = (BoardPosition) (rank_num * 8 + file_num);
    }
    return position;
}
