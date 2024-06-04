#include "Tracking.h"
#include "Handlers/PlayerHandler.h"
#include "Rendering/RenderingInterface.h"
#include "Rendering/FileRendering.h"
#include "Rendering/StreamRendering.h"
#include "Input/Defines.h"
#include <iostream>

Tracking :: Tracking(PlayerHandler* new_handler, std::string file_name) : handler_(new_handler) {
    rendering_ = new FileRendering(file_name);
}

Tracking :: Tracking(PlayerHandler* new_handler, std::ostream &out) : handler_(new_handler) {
    rendering_ = new StreamRendering(out);
}

void Tracking::update(Command* command){
    if(dynamic_cast<ChangeDifficulty*>(command) != nullptr){
        rendering_->print_message(Messages::ChangeDifficulty);
    }
    if(dynamic_cast<ChangeFieldSize*>(command) != nullptr) {
        rendering_->print_message(Messages::ChangeSize);
    }
    if(dynamic_cast<ExitGame*>(command) != nullptr){
        rendering_->print_message(Messages::Exit);
    }
    if(dynamic_cast<GoMainMenu*>(command) != nullptr){
        rendering_->print_message(Messages::GoMainMenu);
    }
    if(dynamic_cast<MovePlayer*>(command) != nullptr){
        rendering_->print_game(handler_);
    }
    if(dynamic_cast<RestartGame*>(command) != nullptr){
        rendering_->print_message(Messages::Restart);
        rendering_->print_game(handler_);
    }
    if(dynamic_cast<StartGame*>(command) != nullptr){
        rendering_->print_message(Messages::Start);
        rendering_->print_game(handler_);
    }
}

void Tracking::update(GameState* state){
    if(dynamic_cast<WinState*>(state) != nullptr){
        rendering_->print_message(Messages::Win);
    }
    if(dynamic_cast<LoseState*>(state) != nullptr){
        rendering_->print_message(Messages::Lose);
    }
}