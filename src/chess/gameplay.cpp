#include "chess/game.hpp"
#include "ZR/core.hpp"

#include<math.h>
#include<string>
#include<memory>

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
                            " " + (*selected_piece).get_name_str() + ".", zr::VERBOSITY_LEVEL::DEBUG);
                    game_state.move_from = position;
                    game_state.possible_moves = get_legal_moves(position);
                    for (ChessMove move : game_state.possible_moves){
                        zr::log("Valid move: " + GameBoard::get_position_str(move.to), zr::VERBOSITY_LEVEL::DEBUG);
                    }
                }else{
                    if (game_state.move_from != InvalidPosition){ // Make capture
                        game_state.move_to = position;
                        ChessMove this_move = is_legal_move(game_state.move_from, game_state.move_to);
                        if (this_move.square_type_at_to != ILLEGAL){
                            make_move(this_move);
                            check_for_checkmate();
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
                        check_for_checkmate();
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

std::vector<ChessMove> ChessGame::get_legal_moves(BoardPosition from){
    auto valid_moves = get_raw_valid_moves(from);

    std::vector<ChessMove> legal_moves;
    for (auto& valid_move : valid_moves){
        ChessMove is_move_legal = {InvalidPosition, InvalidPosition, ILLEGAL};
        bool is_check = does_this_move_leave_me_in_check(valid_move);
        if (is_check == false){
            legal_moves.push_back(valid_move);
        }
    }
    return legal_moves;

}

bool ChessGame::does_this_move_leave_me_in_check(ChessMove move){
    bool will_be_check = false;
    
    // Store states
    std::vector<PieceState> current_piece_states;
    GameState current_game_state = game_state;
    for (ChessPiece* piece : pieces){
        current_piece_states.push_back({(*piece).position, (*piece).color, (*piece).type, (*piece).status, (*piece).has_not_moved_yet});
    }

    // Simulate the move
    ChessGame::make_move(move);

    // Check for checks
    BoardPosition my_kings_position;
    for (ChessPiece* piece : pieces){
        if ((*piece).color == game_state.opponent_player && (*piece).type == KING){
            my_kings_position = (*piece).position;
        }
    }
    for (ChessPiece* piece : pieces){
        if (piece->color == game_state.current_player){
            std::vector<ChessMove> future_moves = get_raw_valid_moves((*piece).position);
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

void ChessGame::make_move(ChessMove requested_move){
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
}

bool ChessGame::check_for_checkmate(){
    zr::log("Now I want to see if checkmate!", zr::VERBOSITY_LEVEL::DEBUG);
    bool is_checkmate = true;
    for (ChessPiece* piece : pieces){
        if (piece->color == game_state.current_player && piece->status == ALIVE){;
            is_checkmate &= (get_legal_moves(piece->position).size() == 0);
            if (!is_checkmate){
                break;
            }
        }
    }
    if (is_checkmate){
        zr::log("Checkmate!");
    }
    return is_checkmate;
}
