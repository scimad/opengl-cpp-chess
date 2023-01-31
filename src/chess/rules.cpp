#include "chess/game.hpp"
#include "ZR/core.hpp"

#include<math.h>
#include<string>
#include<memory>

std::vector<ChessMove> ChessGame::get_raw_valid_moves(BoardPosition from){
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
                SquareType movetype = SquareType::VALID_EMPTY_SQUARE;
                if ((my_color == ChessColors::LIGHT and GameBoard::get_rank(possible_to) == 8) or (my_color == ChessColors::LIGHT and GameBoard::get_rank(possible_to) == 1)){
                    movetype = SquareType::PAWN_PROMOTED;
                    zr::log("Pawn could get promoted!");
                }
                valid_moves.push_back({from, possible_to, movetype});
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
                            // zr::log("1 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
                        }
                        if ((my_color == ChessColors::LIGHT and GameBoard::get_rank(possible_to) == 8) or (my_color == ChessColors::LIGHT and GameBoard::get_rank(possible_to) == 1)){
                            movetype = SquareType::PAWN_PROMOTED;
                            zr::log("Pawn could get promoted!");
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                }else if ((my_color == LIGHT && GameBoard::get_rank(from) == 5) || (my_color == DARK && GameBoard::get_rank(from) == 4)){
                    //En-passant rule
                    zr::log("Could be en-passant");
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
                            // zr::log("2 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
                        }
                        if ((my_color == ChessColors::LIGHT and GameBoard::get_rank(possible_to) == 8) or (my_color == ChessColors::LIGHT and GameBoard::get_rank(possible_to) == 1)){
                            movetype = SquareType::PAWN_PROMOTED;
                            zr::log("Pawn could get promoted!");
                        }
                        valid_moves.push_back({from, possible_to, movetype});
                    }
                }else if ((my_color == LIGHT && GameBoard::get_rank(from) == 5) || (my_color == DARK && GameBoard::get_rank(from) == 4)){
                    //En-passant rule
                    zr::log("Could be en-passant");
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
                            // zr::log("3 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("4 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("4.5 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("5 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                                // zr::log("6 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("7 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("8 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("9 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("10 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("11 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("12 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("13 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("14 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("15 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("16 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("17 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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
                            // zr::log("18 Can give a check at " + GameBoard::get_position_str(possible_to) + " from " + GameBoard::get_position_str(from));
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

    return valid_moves;
}
