#include "../libraries/Point/Point.h"
#include <gtest/gtest.h>
#include <cstdint>

TEST(PointTest, TestDefaultConstructor) {
    Point<int32_t> point;
    EXPECT_EQ(point.get_x(), 0);
    EXPECT_EQ(point.get_y(), 0);
}

TEST(PointTest, TestValueConstructor) {
    Point<int32_t> point(10, -10);
    EXPECT_EQ(point.get_x(), 10);
    EXPECT_EQ(point.get_y(), -10);
}

TEST(PointTest, TestMoveConstructor) {
    Point<int32_t> tmp(5,10);
    Point<int32_t> other(tmp);
    EXPECT_EQ(other.get_x(), 5);
    EXPECT_EQ(other.get_y(), 10);
}

TEST(PointTest, TestCopyConstructor) {
    Point<int32_t> other(Point<int32_t>{20, -5});
    EXPECT_EQ(other.get_x(), 20);
    EXPECT_EQ(other.get_y(), -5);
}

TEST(PointTest, TestAdditionOperator) {
    Point<int32_t> point1(5,15);
    Point<int32_t> point2(-10, 20);
    point1 += point2;
    EXPECT_EQ(point1.get_x(), -5);
    EXPECT_EQ(point1.get_y(), 35);
}

TEST(PointTest, TestAdditionInPlaceOperator) {
    Point<int32_t> point(10,10);
    point = point + Point<int32_t>{-10,5};
    EXPECT_EQ(point.get_x(), 0);
    EXPECT_EQ(point.get_y(), 15);
}
