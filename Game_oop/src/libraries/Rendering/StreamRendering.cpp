#include "StreamRendering.h"
#include "Handlers/PlayerHandler.h"
#include "Game/Engine/GameEngine.h"
#include "Event/MovementEvents/Teleport.h"
#include "Event/NegativeEvents/Trap.h"
#include "Event/PositiveEvents/MedKit.h"
#include <string>

StreamRendering :: StreamRendering(std::ostream &out) : out_(out) {}

void StreamRendering :: print_game(PlayerHandler* handler){
	out_ << std::endl;
    for(int32_t y = 0; y < handler->get_dimensions().get_y(); y++)
	{
		for(int32_t x = 0; x < handler->get_dimensions().get_x(); x++)
		{
            if(Point{x, y} == handler->get_coordinates()) {
                out_ << "[*]";
            } else {
				if(handler->check_enemy(Position{x, y})) {
					out_ << "[!]";
					continue;
				} 
				auto cell = handler->get_cell(Position{x, y});
				if(cell.is_entrance()) out_ << "[0]";
				else if(cell.is_exit()) out_ << "[.]";
				else if(cell.is_wall()) out_ << "[■]";
				else {
					auto *active_event = cell.get_event();
					if(active_event == nullptr) out_ << "[ ]";
					else if(const auto *ptr = dynamic_cast<const Trap*>(active_event); ptr != nullptr) out_ << "[-]";
					else if(const auto *ptr = dynamic_cast<const Teleport*>(active_event); ptr != nullptr) out_ << "[?]";
					else if(const auto *ptr = dynamic_cast<const MedKit*>(active_event); ptr != nullptr) out_ << "[+]";
				}
            }
			out_ << std::flush;
		}
		out_ << std::endl;
	}
	out_ << std::endl;
	
    out_ << "Текущее здоровье: " << handler->get_hp() << "\nТекущие очки: " << handler->get_score() << '\n';

	out_ << std::endl;
}

void StreamRendering :: print_message(Messages message) {
	switch(message) {
		case Messages::ChangeDifficulty:
			out_ << "Изменена сложность игры\n";
			break;
		case Messages::ChangeSize:
			out_ << "Изменен размер игрового поля\n";
			break;
		case Messages::Start:
			out_ << "Начата новая игра\n";
			break;
		case Messages::Restart:
			out_ << "Игра перезапущена\n";
			break;
		case Messages::GoMainMenu:
			out_ << "Произведен вход в главное меню\n";
			out_ << "Вы можете изменить сложность и размер игрового поля\n";
			out_ << "Также вы можете перезапустить игру или начать новую\n";
			break;
		case Messages::Win:
			out_ << "Вы выиграли!\n";
			break;
		case Messages::Lose:
			out_ << "Вы проиграли!\n";
			break;
	}
}