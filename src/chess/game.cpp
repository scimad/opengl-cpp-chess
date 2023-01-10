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

        // TODO: Continue gameplay by checking game_state
        if (position != BoardPosition::InvalidPosition){
            // start game
            if (game_state.paused == true){
                game_state.paused = false;
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
                    get_valid_moves(position);
                }
                else
                {
                    if (game_state.move_from != InvalidPosition){ // Make capture
                        zr::log("Capture " + board.get_position_str(position) +
                                " " + (*selected_piece).get_color_str() +
                                " " + (*selected_piece).get_name_str() + ".");
                        game_state.move_to = position;
                        if (is_legal_move(game_state.move_from, game_state.move_to)){
                            capture(game_state.move_from, game_state.move_to);
                        }
                    }
                }
            }else{
                if (game_state.move_from != InvalidPosition){ // Make move
                    zr::log("Move to empty square " + board.get_position_str(position) + ".");
                    game_state.move_to = position;
                    if (is_legal_move(game_state.move_from, game_state.move_to)){
                        move(game_state.move_from, game_state.move_to);
                    }
                }
            }
        }else{
            game_state.move_from = InvalidPosition;
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

std::vector<BoardPosition> ChessGame::get_valid_moves(BoardPosition from){
    ChessPiece* current_piece = get_piece_at_position(from);

    unsigned int file_from = GameBoard::get_file(from);
    unsigned int rank_from = GameBoard::get_rank(from);

    // unsigned int file_to = GameBoard::get_file(to);
    // unsigned int rank_to = GameBoard::get_rank(to);

    std::vector<BoardPosition> valid_moves;

    BoardPosition possible_to;
    switch ((*current_piece).type)   // (*current_piece).
    {
    case PAWN:
        {
            int direction = 1 - 2 * (int) (*current_piece).color; //LIGHT moves in direction = 1, DARK moves in direction = -1
            // One step move rule
            possible_to = (BoardPosition) ((int) from + direction * 8);
            if (!get_piece_at_position(possible_to))
            {
                valid_moves.push_back(possible_to);
            }
            // Two step move rule
            if ((*current_piece).has_not_moved_yet){
                possible_to = (BoardPosition) ((int) from + direction * 16);
                BoardPosition one_rank_ahead = (BoardPosition) ((int) from + direction * 8);
                if (!get_piece_at_position(possible_to) && !get_piece_at_position(one_rank_ahead))
                {
                    valid_moves.push_back(possible_to);
                }
            }
            // Capture rule for Right diagonal of PAWN
            if (((*current_piece).color == LIGHT && GameBoard::get_file(from) != BoardFile::H) || (((*current_piece).color == DARK && GameBoard::get_file(from) != BoardFile::A))){
                // Not the player's right most file
                possible_to = (BoardPosition) ((int) from + direction * 8 + 1);
                ChessPiece* target_piece = get_piece_at_position(possible_to);
                if (target_piece){
                    if ((*target_piece).color != (*current_piece).color)
                    valid_moves.push_back(possible_to);
                }else if (((*current_piece).color == LIGHT && GameBoard::get_rank(from) == 5) || ((*current_piece).color == DARK && GameBoard::get_rank(from) == 4)){
                    //En-passant rule
                    ChessMove last_move = moves.top();
                    if (((*(get_piece_at_position(last_move.to))).type == PAWN) && (BoardFile)(GameBoard::get_file(from) + direction) == GameBoard::get_file(last_move.from) && ((int) GameBoard::get_rank(last_move.from) - (int) GameBoard::get_rank(last_move.to) == 2 * direction)){
                        valid_moves.push_back(possible_to);
                    }
                }
            }

            // Capture rule for Left diagonal of PAWN
            if (((*current_piece).color == LIGHT && GameBoard::get_file(from) != BoardFile::A) || (((*current_piece).color == DARK && GameBoard::get_file(from) != BoardFile::H))){
                // Not the player's left most file
                possible_to = (BoardPosition) ((int) from + direction * 8 - 1);
                ChessPiece* target_piece = get_piece_at_position(possible_to);
                if (target_piece){
                    if ((*target_piece).color != (*current_piece).color)
                    valid_moves.push_back(possible_to);
                }else if (((*current_piece).color == LIGHT && GameBoard::get_rank(from) == 5) || ((*current_piece).color == DARK && GameBoard::get_rank(from) == 4)){
                    //En-passant rule
                    ChessMove last_move = moves.top();
                    if (((*(get_piece_at_position(last_move.to))).type == PAWN) && GameBoard::get_file(from) - direction == GameBoard::get_file(last_move.from) && ((int) GameBoard::get_rank(last_move.from) - (int) GameBoard::get_rank(last_move.to) == 2 * direction)){
                        valid_moves.push_back(possible_to);
                    }
                }
            }

            // TODO: Contiune from here
            for (BoardPosition pos : valid_moves){
                zr::log("Possible move: " + GameBoard::get_position_str(pos));
            }
        }
        break;
    default:
        break;
    }
    return valid_moves;
}

bool ChessGame::is_legal_move(BoardPosition from, BoardPosition to){
    bool is_move_valid = true;
    // TODO: WRITE LEGAL MOVE LOGIC
    return is_move_valid;
};

void ChessGame::move(BoardPosition from, BoardPosition to){
    ChessPiece* current_piece = get_piece_at_position(from);
    (*current_piece).position = to;
    game_state.current_player = (ChessColors)(1-game_state.current_player); // Alternate between LIGHT and DARK
    
    // TODO : check if the move is a capture or promotion or castling
    moves.push({from, to, false, false});
    
    // TODO: Implement pawn promotion

    game_state.move_from = InvalidPosition;
    game_state.move_to = InvalidPosition;
    (*current_piece).has_not_moved_yet = false;
}

void ChessGame::capture(BoardPosition by, BoardPosition at){
    ChessPiece* current_piece = get_piece_at_position(by);
    ChessPiece* captured_piece = get_piece_at_position(at);
    (*captured_piece).position = InvalidPosition;
    (*captured_piece).status = DEAD;
    move(by, at);
};

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
