#include "chess/game.hpp"

int main(){
    zr::log_level = zr::VERBOSITY_LEVEL::INFO;
    ChessGame game;
    game.run();
    return 0;
}
