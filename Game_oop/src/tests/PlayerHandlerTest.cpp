#include "../libraries/Player/Player.h"
#include "../libraries/World/Field.h"
#include "../libraries/Handlers/PlayerHandler.h"
#include "../libraries/Event/MovementEvents/Teleport.h"
#include "../libraries/Event/PositiveEvents/MedKit.h"
#include "../libraries/Event/NegativeEvents/Trap.h"
#include <gtest/gtest.h>

TEST(PlayerHandlerTest, TestPlayerConstructor) {
    Player* pl = new Player();
    PlayerHandler act(pl);
    EXPECT_EQ(pl->get_hp(), act.get_hp());
    EXPECT_EQ(pl->get_score(), act.get_score());
}

TEST(PlayerHandlerTest, TestSetCoordinates) {
    Player* pl = new Player();
    Field* field = new Field();
    PlayerHandler act(pl, field);
    act.set_coordinates({2,2});
    EXPECT_EQ(act.get_coordinates(), (Position{2, 2}));
}

TEST(PlayerHandlerTest, TestSetCoordinatesInWall) {
    Player* pl = new Player();
    Field* field = new Field();
    PlayerHandler act(pl, field);
    field->create_wall(Position{2,2});
    try {
        act.set_coordinates(Position{2,2});
    } catch (std::invalid_argument const& err) {
        EXPECT_EQ(err.what(), std::string("Клетка поля непроходима"));
    }
}

TEST(PlayerHandlerTest, TestMovement) {
    Player* pl = new Player();
    Field* field = new Field();
    PlayerHandler act(pl, field);
    act.set_coordinates(Position{0,0});
    act.movement(3, PlayerHandler::Direction::Right);
    EXPECT_EQ(act.get_coordinates(), (Position{3,0}));
}


TEST(PlayerHandlerTest, TestMovementInWall) {
    Player* pl = new Player();
    Field* field = new Field();
    PlayerHandler act(pl, field);
    act.set_coordinates(Position{0,0});
    field->create_wall(Position{0,3});
        try {
        act.movement(4, PlayerHandler::Direction::Down);
    } catch (std::invalid_argument const& err) {
        EXPECT_EQ(err.what(), std::string("Клетка поля непроходима"));
    }
}

TEST(PlayerHandlerTest, TestMedKitEvent) {
    Player* pl = new Player(50,0);
    Field* field = new Field();
    PlayerHandler act(pl, field);
    field->get_cell(Position{1,1}).add_event(new MedKit(30));
    act.set_coordinates(Position{1,1});
    EXPECT_EQ(act.get_hp(), 80);
}

TEST(PlayerHandlerTest, TestTrapEvent) {
    Player* pl = new Player(50,0);
    Field* field = new Field();
    PlayerHandler act(pl, field);
    field->get_cell(Position{1,1}).add_event(new Trap(20));
    act.set_coordinates(Position{1,1});
    EXPECT_EQ(act.get_hp(), 30);
}

TEST(PlayerHandlerTest, TestTeleportEvent) {
    Player* pl = new Player(50,0);
    Field* field = new Field();
    PlayerHandler act(pl, field);
    field->get_cell(Position{1,1}).add_event(new Teleport(Position{5,5}));
    act.set_coordinates(Position{1,1});
    EXPECT_EQ(act.get_coordinates(),(Position{5,5}));
}