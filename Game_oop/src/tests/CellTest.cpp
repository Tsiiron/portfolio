#include "../libraries/World/Cell.h"
#include <gtest/gtest.h>

TEST(CellTest, TestDefaultConstructor) {
    Cell cell;
    EXPECT_EQ(cell.is_passable(), true);
}

TEST(CellTest, TestTypeConstructor) {
    {
        Cell cell(Cell::Type::ENTRANCE);
        EXPECT_EQ(cell.is_entrance(), true);
        EXPECT_EQ(cell.is_exit(), false);
        EXPECT_EQ(cell.is_passable(), true);
    }

    {
        Cell cell(Cell::Type::WALL);
        EXPECT_EQ(cell.is_entrance(), false);
        EXPECT_EQ(cell.is_wall(), true);
        EXPECT_EQ(cell.is_passable(), false);
    }
}

TEST(CellTest, TestMoveConstructor) {
    Cell tmp(Cell::Type::PASSABLE);
    Cell other(tmp);

    EXPECT_EQ(other.is_entrance(), false);
    EXPECT_EQ(other.is_wall(), false);
    EXPECT_EQ(other.is_passable(), true);
}

TEST(CellTest, TestCopyConstructor) {
    Cell other(Cell{Cell::Type::EXIT});
    EXPECT_EQ(other.is_entrance(), false);
    EXPECT_EQ(other.is_exit(), true);
    EXPECT_EQ(other.is_passable(), true);
}