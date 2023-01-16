#include "chess/game.hpp"
#include "ZR/core.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include<math.h>
#include<string>
#include<memory>

ChessGame::ChessGame():
    board("../res/basic.shader", "../assets/Board.png"), square("../res/basic.shader", "../assets/box.png"), end_and_exit(false), touch_to_move_rule(false)
{
    //8 light pawns and 8 dark pawns
    for (size_t i=0; i< 8; i++)
    {
        pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_plt45.svg.png", LIGHT, PAWN, board.get_position_from_str(std::string({char(65+i), '2'}))));
        pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_pdt45.svg.png", DARK, PAWN, board.get_position_from_str(std::string({char(65+i), '7'}))));
    }

    //light Queen and dark Queen
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_qlt45.svg.png", LIGHT, QUEEN, D1));
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_qdt45.svg.png", DARK, QUEEN, D8));

    //light King and dark King
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_klt45.svg.png", LIGHT, KING, E1));
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_kdt45.svg.png", DARK, KING, E8));

    //2 light bishops and 2 dark bishops
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_blt45.svg.png", LIGHT, BISHOP, C1));
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_blt45.svg.png", LIGHT, BISHOP, F1));
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_bdt45.svg.png", DARK, BISHOP, C8));
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_bdt45.svg.png", DARK, BISHOP, F8));

    //2 light knights and 2 dark knights
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_nlt45.svg.png", LIGHT, KNIGHT, B1));
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_nlt45.svg.png", LIGHT, KNIGHT, G1));
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_ndt45.svg.png", DARK, KNIGHT, B8));
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_ndt45.svg.png", DARK, KNIGHT, G8));

    //2 light rooks and 2 dark rooks
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_rlt45.svg.png", LIGHT, ROOK, A1));
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_rlt45.svg.png", LIGHT, ROOK, H1));
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_rdt45.svg.png", DARK, ROOK, A8));
    pieces.push_back(new ChessPiece("../res/basic.shader", "../assets/Chess_rdt45.svg.png", DARK, ROOK,H8));

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
        zr::log(chess_piece->get_name_str() + " is at "  + board.get_position_str(chess_piece->position) + ".", zr::VERBOSITY_LEVEL::DEBUG);
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
                game_state.possible_moves.clear();
                zr::log("Game timer started.");
                // TODO: Start ChessTimer
            }
            ChessPiece* selected_piece = get_piece_at_position(position);
            if (selected_piece != nullptr){
                if (game_state.current_player == (*selected_piece).color){  // Choosing a piece to move
                    zr::log("Player " + (*selected_piece).get_color_str() +
                            ": Move my " + board.get_position_str(position) +
                            " " + (*selected_piece).get_name_str() + ".");
                    game_state.move_from = position;
                    game_state.possible_moves = get_valid_moves(position);
                    for (ChessMove move : game_state.possible_moves){
                        zr::log("Valid move: " + GameBoard::get_position_str(move.to), zr::VERBOSITY_LEVEL::INFO);
                    }
                }else{
                    if (game_state.move_from != InvalidPosition){ // Make capture
                        game_state.move_to = position;
                        ChessMove this_move = is_legal_move(game_state.move_from, game_state.move_to);
                        if (this_move.square_type_at_to != ILLEGAL){
                            make_move(this_move);
                        }
                    }
                    game_state.possible_moves.clear();
                }
            }else{
                if (game_state.move_from != InvalidPosition){ // Make move
                    zr::log("Move to empty square " + board.get_position_str(position) + ".", zr::DEBUG);
                    game_state.move_to = position;
                    ChessMove this_move = is_legal_move(game_state.move_from, game_state.move_to);
                    if (this_move.square_type_at_to != ILLEGAL){
                        make_move(this_move);
                    }
                }
                game_state.possible_moves.clear();
            }
        }else{
            game_state.move_from = InvalidPosition;
            game_state.possible_moves.clear();
        }
    }
    glui.button_actions_queue.clear();
}

void ChessGame::run(){

    zr::log(get_color_name(game_state.current_player) + " color player to make a move.", zr::VERBOSITY_LEVEL::INFO);

    /* Loop until the user closes the window */
    while (!glui.exit_flag || (*this).end_and_exit){
        // processInput();
        glui.redraw_gl_contents(pieces, board, game_state);
        glui.refresh_gl_inputs();

        process_requests();
    }

    glfwTerminate(); // Refer to the notes on README.md of this project
    zr::log("OpenGL environment terminating gracefully.");
}

std::vector<ChessMove> ChessGame::get_valid_moves(BoardPosition from, bool check_for_checks){
    ChessPiece* current_piece = get_piece_at_position(from);

    unsigned int file_from = GameBoard::get_file(from);
    unsigned int rank_from = GameBoard::get_rank(from);
    const ChessColors& my_color = (*current_piece).color;
    const PieceType& my_type = (*current_piece).type;
    const bool& not_moved_yet = (*current_piece).has_not_moved_yet;

    // unsigned int file_to = GameBoard::get_file(to);
    // unsigned int rank_to = GameBoard::get_rank(to);

    std::vector<ChessMove> valid_moves;

    BoardPosition possible_to;
    ChessPiece* target_piece;

    switch (my_type)   // (*current_piece).
    {
    case PAWN:
        {
            int direction = 1 - 2 * (int) my_color; //LIGHT moves in direction = 1, DARK moves in direction = -1
            // One step move rule
            possible_to = (BoardPosition) ((int) from + direction * 8);
            if (!get_piece_at_position(possible_to))
            {
                valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE });
            }
            // Two step move rule
            if (not_moved_yet){
                possible_to = (BoardPosition) ((int) from + direction * 16);
                BoardPosition one_rank_ahead = (BoardPosition) ((int) from + direction * 8);
                if (!get_piece_at_position(possible_to) && !get_piece_at_position(one_rank_ahead))
                {
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }
            }
            // Capture rule for Right diagonal of PAWN
            if ((my_color == LIGHT && GameBoard::get_file(from) != BoardFile::H) || ((my_color == DARK && GameBoard::get_file(from) != BoardFile::A))){
                // Check on current piece's right
                possible_to = (BoardPosition) ((int) from + direction * 8 + direction);
                target_piece = get_piece_at_position(possible_to);
                if (target_piece){
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                }else if ((my_color == LIGHT && GameBoard::get_rank(from) == 5) || (my_color == DARK && GameBoard::get_rank(from) == 4)){
                    //En-passant rule
                    ChessMove last_move = moves.top();
                    // ((int) GameBoard::get_rank(last_move.from) - (int) GameBoard::get_rank(last_move.to) == 2 * direction)
                    if (((*game_state.last_moved_piece).type == PAWN) && (BoardFile)(GameBoard::get_file(from) + direction) == GameBoard::get_file(last_move.from) &&  last_move.to == GameBoard::get_position_ahead(last_move.from, game_state.opponent_player, 2)){
                        valid_moves.push_back({from, possible_to, SquareType::EN_PASSANT_CAPTURE});
                    }
                }
            }

            // Capture rule for Left diagonal of PAWN
            if ((my_color == LIGHT && GameBoard::get_file(from) != BoardFile::A) || ((my_color == DARK && GameBoard::get_file(from) != BoardFile::H))){
                // Check on current piece's left
                possible_to = (BoardPosition) ((int) from + direction * 8 - direction);
                target_piece = get_piece_at_position(possible_to);
                if (target_piece){
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                }else if ((my_color == LIGHT && GameBoard::get_rank(from) == 5) || (my_color == DARK && GameBoard::get_rank(from) == 4)){
                    //En-passant rule
                    ChessMove last_move = moves.top();
                    if (((*game_state.last_moved_piece).type == PAWN) && GameBoard::get_file(GameBoard::get_position_on_left(from, my_color))== GameBoard::get_file(last_move.from) &&  last_move.to == GameBoard::get_position_ahead(last_move.from, game_state.opponent_player, 2)){
                        valid_moves.push_back({from, possible_to, SquareType::EN_PASSANT_CAPTURE});
                    }
                }
            }
        }
        break;
    case ROOK:
        {
            int n_moves;
            // rook left
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_on_left(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }

            // rook right
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_on_right(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }

            // rook ahead
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_ahead(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }

            // rook back
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_back(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);

                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }
        }
        break;
    case KNIGHT:
        {
            for (unsigned int i = 0; i<8; i++){
                int a = (pow(-1, i / 2)) * (pow(-1, i / 4))* (1 + i/4);
                int b = (pow(-1, (i) % 2)) * (2 - i/4);
                possible_to = GameBoard::get_position((BoardFile)((int) GameBoard::get_file(from) + a), (BoardRank)(int (GameBoard::get_rank(from) + b)));
                if (possible_to != InvalidPosition){
                    target_piece = get_piece_at_position(possible_to);
                    if (!target_piece){
                        valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                    }else{
                        if ((*target_piece).color == game_state.opponent_player){
                            SquareType movetype = SquareType::NORMAL_CAPTURE;
                            if ((*target_piece).type == KING){
                                movetype = SquareType::KING_CHECKED;
                                zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                            }
                            valid_moves.push_back({from, possible_to, movetype});
                        }
                    }
                }
            }
        }
        break;
    case BISHOP:
        {
            int n_moves;
            // bishop front left
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_on_front_left(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }

            // bishop front right
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_on_front_right(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }

            // bishop back left
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_on_back_left(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }

            // bishop back right
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_on_back_right(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }
        }
        break;

    case QUEEN:
        {
            int n_moves;
            // queen front left
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_on_front_left(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }

            // queen front right
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_on_front_right(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }

            // queen back left
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_on_back_left(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }

            // queen back right
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_on_back_right(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }
        }

        {
            int n_moves;
            // queen left
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_on_left(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }

            // queen right
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_on_right(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }

            // queen ahead
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_ahead(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);
                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }

            // queen back
            n_moves = 0;
            while (true){
                n_moves++;
                possible_to = GameBoard::get_position_back(from, my_color, n_moves);
                if (possible_to == InvalidPosition){
                    break;
                }
                target_piece = get_piece_at_position(possible_to);

                if (!target_piece){
                    valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
                }else{
                    if ((*target_piece).color == game_state.opponent_player){
                        SquareType movetype = SquareType::NORMAL_CAPTURE;
                        if ((*target_piece).type == KING){
                            movetype = SquareType::KING_CHECKED;
                            zr::log("Can give a check at " + GameBoard::get_position_str(possible_to));
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                    break;
                }
            }
        }
        break;

    case KING:
    {
        // left
        possible_to = GameBoard::get_position_on_left(from, my_color);
        if (possible_to != InvalidPosition){
            target_piece = get_piece_at_position(possible_to);
            if (!target_piece){
                valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
            }else{
                if ((*target_piece).color == game_state.opponent_player){
                    valid_moves.push_back({from, possible_to, SquareType::NORMAL_CAPTURE});
                }
            }
        }

        possible_to = GameBoard::get_position_on_right(from, my_color);
        if (possible_to != InvalidPosition){
            target_piece = get_piece_at_position(possible_to);
            if (!target_piece){
                valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
            }else{
                if ((*target_piece).color == game_state.opponent_player){
                    valid_moves.push_back({from, possible_to, SquareType::NORMAL_CAPTURE});
                }
            }
        }

        possible_to = GameBoard::get_position_ahead(from, my_color);
        if (possible_to != InvalidPosition){
            target_piece = get_piece_at_position(possible_to);
            if (!target_piece){
                valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
            }else{
                if ((*target_piece).color == game_state.opponent_player){
                    valid_moves.push_back({from, possible_to, SquareType::NORMAL_CAPTURE});
                }
            }
        }

        possible_to = GameBoard::get_position_back(from, my_color);
        if (possible_to != InvalidPosition){
            target_piece = get_piece_at_position(possible_to);
            if (!target_piece){
                valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
            }else{
                if ((*target_piece).color == game_state.opponent_player){
                    valid_moves.push_back({from, possible_to, SquareType::NORMAL_CAPTURE});
                }
            }
        }

        possible_to = GameBoard::get_position_on_front_left(from, my_color);
        if (possible_to != InvalidPosition){
            target_piece = get_piece_at_position(possible_to);
            if (!target_piece){
                valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
            }else{
                if ((*target_piece).color == game_state.opponent_player){
                    valid_moves.push_back({from, possible_to, SquareType::NORMAL_CAPTURE});
                }
            }
        }

        possible_to = GameBoard::get_position_on_front_right(from, my_color);
        if (possible_to != InvalidPosition){
            target_piece = get_piece_at_position(possible_to);
            if (!target_piece){
                valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
            }else{
                if ((*target_piece).color == game_state.opponent_player){
                    valid_moves.push_back({from, possible_to, SquareType::NORMAL_CAPTURE});
                }
            }
        }

        possible_to = GameBoard::get_position_on_back_left(from, my_color);
        if (possible_to != InvalidPosition){
            target_piece = get_piece_at_position(possible_to);
            if (!target_piece){
                valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
            }else{
                if ((*target_piece).color == game_state.opponent_player){
                    valid_moves.push_back({from, possible_to, SquareType::NORMAL_CAPTURE});
                }
            }
        }

        possible_to = GameBoard::get_position_on_back_right(from, my_color);
        if (possible_to != InvalidPosition){
            target_piece = get_piece_at_position(possible_to);
            if (!target_piece){
                valid_moves.push_back({from, possible_to, SquareType::VALID_EMPTY_SQUARE});
            }else{
                if ((*target_piece).color == game_state.opponent_player){
                    valid_moves.push_back({from, possible_to, SquareType::NORMAL_CAPTURE});
                }
            }
        }
    }
        break;
    default:
        break;
    }

    if (check_for_checks)
    {
        std::vector<ChessMove> legal_moves;
        for (auto& valid_move : valid_moves){
            ChessMove is_move_legal = {InvalidPosition, InvalidPosition, ILLEGAL};
            bool is_check = does_this_move_leave_me_in_check(valid_move);
            if (is_check == false){
                legal_moves.push_back(valid_move);
            }
        }
        valid_moves = legal_moves;
    }

    return valid_moves;

}

bool ChessGame::does_this_move_leave_me_in_check(ChessMove move){
    bool will_be_check = false;
    std::vector<PieceState> current_piece_states;
    GameState current_game_state = game_state;
    for (ChessPiece* piece : pieces){
        current_piece_states.push_back({(*piece).position, (*piece).color, (*piece).type, (*piece).status, (*piece).has_not_moved_yet});
    }

    ChessGame::make_move(move, false);

    BoardPosition my_kings_position;
    for (ChessPiece* piece : pieces){
        if ((*piece).color == game_state.opponent_player && (*piece).type == KING){
            my_kings_position = (*piece).position;
        }
    }
    for (ChessPiece* piece : pieces){
        if (piece->color == game_state.current_player){
            std::vector<ChessMove> future_moves = get_valid_moves((*piece).position, false);
            for (ChessMove future_move : future_moves){
                if  (future_move.to == my_kings_position){
                    will_be_check = true;
                }
            }
        }
    }

    // Revert state
    for (size_t i = 0; i< pieces.size(); ++i){
        pieces[i]->position = current_piece_states[i].position;
        pieces[i]->color = current_piece_states[i].color;
        pieces[i]->type = current_piece_states[i].type;
        pieces[i]->status = current_piece_states[i].status;
        pieces[i]->has_not_moved_yet = current_piece_states[i].has_not_moved_yet;
    }

    game_state = current_game_state;

    return will_be_check;
}

ChessMove ChessGame::is_legal_move(BoardPosition from, BoardPosition to){
    ChessMove is_move_legal = {InvalidPosition, InvalidPosition, ILLEGAL};

    // game_state.possible_moves = get_valid_moves(from);
    for (auto& valid_move : game_state.possible_moves){
        bool is_check = false;
        if (valid_move.to == to){
            is_check |= does_this_move_leave_me_in_check(valid_move);
            if (is_check == false){
                is_move_legal = valid_move;
                break;
            }
        }
    }
    return is_move_legal;
};

void ChessGame::make_move(ChessMove requested_move, bool is_real_move){
    // BoardPosition from, BoardPosition to){
    BoardPosition from = requested_move.from;
    BoardPosition to = requested_move.to;
    SquareType move_type = requested_move.square_type_at_to;
    ChessPiece* current_piece = get_piece_at_position(from);

    switch (requested_move.square_type_at_to){
        case VALID_EMPTY_SQUARE:
        {
            (*current_piece).position = to;
        }
            break;
        case NORMAL_CAPTURE:
        {
            ChessPiece* captured_piece = get_piece_at_position(to);
            (*captured_piece).position = InvalidPosition;
            (*captured_piece).status = DEAD;
            (*current_piece).position = to;
        }
            break;
        case EN_PASSANT_CAPTURE:
        {
            ChessPiece* captured_piece = get_piece_at_position(GameBoard::get_position_back(to, game_state.current_player));
            (*captured_piece).position = InvalidPosition;
            (*captured_piece).status = DEAD;
            (*current_piece).position = to;
        }
            break;
        case KING_CASTLE:
            break;
        case PAWN_PROMOTED:
            break;
        default:
            break;
    }
    // TODO : check if the move is promotion or castling
    // TODO: Implement pawn promotion

    (*current_piece).has_not_moved_yet = false;
    game_state.last_moved_piece = current_piece;

    game_state.move_from = InvalidPosition;
    game_state.move_to = InvalidPosition;
    game_state.selected_position = InvalidPosition;
    game_state.possible_moves.clear();

    // save history of moves.
    moves.push(requested_move);

    // Alternate between LIGHT and DARK
    game_state.opponent_player = game_state.current_player;
    game_state.current_player = (ChessColors)(1-game_state.current_player);

    if (is_real_move){
        zr::log("Now I want to see if checkmate!");

        bool is_checkmate = true;
        for (ChessPiece* piece : pieces){
            if (piece->color == game_state.current_player && piece->status == ALIVE){;
                is_checkmate &= (get_valid_moves(piece->position, true).size() == 0);

                if (!is_checkmate){
                    break;
                }
            }
        }
        if (is_checkmate){
            zr::log("Checkmate!");
        }
    }
}

void ChessGame::capture(ChessMove capturing_move){
};
