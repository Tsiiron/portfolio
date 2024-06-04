#include "MovePlayer.h"
#include "Game/State/WinState.h"
#include "Game/State/LoseState.h"

MovePlayer :: MovePlayer(PlayerHandler::Direction direction) : direction_(direction) {}

void MovePlayer :: execute(GameEngine &game) {
    game.move_player(1, direction_);
    if(game.handler()->get_coordinates() == game.field()->get_finish_point()) {
        game.set_state(new WinState);
        
    }
    if(game.handler()->get_hp() == 0) {
        game.set_state(new LoseState);
    }
}