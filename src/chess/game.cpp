#include "game.hpp"
#include "ZR/core.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include<string>
#include<memory>

ChessGame::ChessGame():
    board("../res/basic.shader", "../assets/Board.png"), end_and_exit(false), touch_to_move_rule(false)
{
    //8 light pawns and 8 dark pawns
    for (size_t i=0; i< 8; i++)
    {
        pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_plt45.svg.png", LIGHT, PAWN, board.get_position_from_str(std::string({char(65+i), '2'}))));
        pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_pdt45.svg.png", DARK, PAWN, board.get_position_from_str(std::string({char(65+i), '7'}))));
    }

    //light Queen and dark Queen
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_qlt45.svg.png", LIGHT, QUEEN, D1));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_qdt45.svg.png", DARK, QUEEN, D8));

    //light King and dark King
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_klt45.svg.png", LIGHT, KING, E1));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_kdt45.svg.png", DARK, KING, E8));

    //2 light bishops and 2 dark bishops
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_blt45.svg.png", LIGHT, BISHOP, C1));
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_blt45.svg.png", LIGHT, BISHOP, F1));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_bdt45.svg.png", DARK, BISHOP, C8));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_bdt45.svg.png", DARK, BISHOP, F8));

    //2 light knights and 2 dark knights
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_nlt45.svg.png", LIGHT, KNIGHT, B1));
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_nlt45.svg.png", LIGHT, KNIGHT, G1));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_ndt45.svg.png", DARK, KNIGHT, B8));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_ndt45.svg.png", DARK, KNIGHT, G8));

    //2 light rooks and 2 dark rooks
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_rlt45.svg.png", LIGHT, ROOK, A1));
    pieces.push_back(new ChessPiece("../res/light.shader", "../assets/Chess_rlt45.svg.png", LIGHT, ROOK, H1));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_rdt45.svg.png", DARK, ROOK, A8));
    pieces.push_back(new ChessPiece("../res/dark.shader", "../assets/Chess_rdt45.svg.png", DARK, ROOK,H8));

    game_state.selected_position = BoardPosition::InvalidPosition;

}

// ChessGame::ChessGame(GameState current_state){

// }

ChessGame::~ChessGame(){
    for (auto& piece : pieces){
        delete piece;
    }
}

ChessPiece* ChessGame::get_piece_at_position(BoardPosition position){
    for (ChessPiece* chess_piece : pieces){
        zr::log(chess_piece->get_name_str() + " is at "  + board.get_position_str(chess_piece->position), zr::VERBOSITY_LEVEL::DEBUG);
        if ((*chess_piece).position == position){
            return chess_piece;
        }
    }
    return nullptr;
}

void ChessGame::process_requests() {
    for (auto clickevent : glui.button_actions_queue){
        glm::vec2 board_xy = glui.transform_xy_window_to_board(board, std::get<1>(clickevent));
        BoardPosition position = board.get_board_position_from_xy(board_xy);
        game_state.selected_position = position;

        if (position != BoardPosition::InvalidPosition){
            // start game
            if (game_state.paused == true){
                game_state.paused = false;
                zr::log("Game timer started");
                // TODO: Start ChessTimer
            }
            zr::log("Selecting " + board.get_position_str(position));

            // TODO: Find the piece based on the position and continue gameplay
            {
                ChessPiece* selected_piece = get_piece_at_position(position);
                if (selected_piece != nullptr){
                    zr::log("Selected piece is a: " + (*selected_piece).get_color_str() + " " + (*selected_piece).get_name_str());
                }else{
                    zr::log(board.get_position_str(position)  + " is an empty square.", zr::VERBOSITY_LEVEL::INFO);
                }
            }

        }else{
            if (touch_to_move_rule == false){
                game_state.move_from = InvalidPosition;
            }
        }
    }

    glui.button_actions_queue.clear();
}

void ChessGame::run(){

    zr::log(get_color_name(game_state.current_player) + " color player to make a move.", zr::VERBOSITY_LEVEL::INFO);

    /* Loop until the user closes the window */
    while (!glui.exit_flag || (*this).end_and_exit){
        // processInput();
        glui.redraw_gl_contents(pieces, board);
        glui.refresh_gl_inputs();

        process_requests();
    }

    glfwTerminate(); // Refer to the notes on README.md of this project
    zr::log("OpenGL environment terminating gracefully.");
}



GameState::GameState() :
    paused(true),
    current_player(ChessColors::LIGHT),
    selected_position(BoardPosition::InvalidPosition),
    total_moves_count(0),
    irreversible_moves_count(0),
    repeated_moves_count(0),
    is_checked(false),
    is_white_castled(false),
    is_black_castled(false),
    move_from(BoardPosition::InvalidPosition),
    move_to(BoardPosition::InvalidPosition)
{
    zr::log("New game started.", zr::INFO);
}

GameState::~GameState()
{
}
