#include "../libraries/World/Field.h"
#include "../libraries/Point/Point.h"
#include "Event/NegativeEvents/Trap.h"
#include <gtest/gtest.h>

TEST(FieldTest, TestDefaultConstructor) {
    Field field;
    EXPECT_EQ(field.get_dimensions(), Dimension(10, 10));
}

TEST(FieldTest, TestDimensionConstructor) {
    Field field(20,20);
    EXPECT_EQ(field.get_dimensions(), Dimension(20,20));
}

TEST(FieldTest, TestSetCell) {
    Field field;
    EXPECT_EQ(field.get_cell((Position(0,0))).is_passable(), true);
    field.get_cell(Position(0,0)).set_type(Cell::Type::WALL);
    EXPECT_EQ(field.get_cell((Position(0,0))).is_wall(), true);
}

TEST(FieldTest, TestFieldMoveContructor) {
    Field field(11, 11);
	Field copy = std::move(field);

	EXPECT_EQ(copy.get_dimensions(), Dimension(11, 11));
	EXPECT_EQ(copy.get_start_point(), Position(-1, -1));
	EXPECT_EQ(copy.get_finish_point(), Position(-1, -1));

}

TEST(FieldTest, TestIsOnField) {
    Field field;

    EXPECT_EQ(field.is_on_map({9,9}), true);
    EXPECT_EQ(field.is_on_map({0,0}), true);
    EXPECT_EQ(field.is_on_map({10,10}), false);
    EXPECT_EQ(field.is_on_map({-1,-1}), false);

}

TEST(FieldTest, TestGetCell) {
    Field field;
    field.create_wall({3,3});
    EXPECT_EQ(field.get_cell({3,3}).is_wall(), true);
}