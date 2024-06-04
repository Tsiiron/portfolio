#include <iostream>
#include "Game/Engine/GameEngine.h"
#include "Input/FileInput.h"
#include "Input/StreamInput.h"
#include "Game/State/PlayingState.h"
#include "Game/State/MainMenuState.h"
#include "Enemies/EnemyDefines.h"
#include "Enemies/Enemy.h"
#include "FieldGenerator/DefaultLevels/DefaultLevelGenerator.h"

int main()
{
    const std::string directory = "/home/reuzy/VS_Projects/oop/lb7/";
    const std::string binds = "binds.txt";
    const std::string actions = "test_input.txt";
    StreamInput* input = new StreamInput(directory + binds, std::cin);
    // FileInput* input = new FileInput(directory + binds, directory + actions);

    GameEngine *game = new GameEngine(input);
    game->play_game();

    // Player* player_ = new Player;
    // PlayerHandler* handler_ = new PlayerHandler(player_);
    // DefaultLevelGenerator gen(DefaultLevelGenerator::MAP_SIZE::SMALL, DefaultLevelGenerator::DIFFICULTY::EASY);
    // Field* field_ = gen.generate(handler_);
    // handler_->set_field(field_);
    // handler_->set_coordinates(field_->get_start_point());

    // std::vector<EnemyBase*> new_vector;
    // for(auto& enemy : field_->get_enemies()) {
    //     new_vector.push_back(enemy);
    // }
    // std::cout << new_vector.size();

    return 0;
}