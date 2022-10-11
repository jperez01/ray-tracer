#include <gtest/gtest.h>
#include "patterns/striped_pattern.h"

TEST(patternTest, createStripedPattern) {
    Color black(0, 0, 0);
    Color white(1, 1, 1);
    StripedPattern pattern(white, black);

    EXPECT_TRUE(pattern.colorA() == white);
    EXPECT_TRUE(pattern.colorB() == black);
}

TEST(patternTest, testColorAt) {
    Color black(0, 0, 0);
    Color white(1, 1, 1);
    StripedPattern pattern(white, black);

    Tuple point = Point(1, 0, 0);
    Color result = pattern.getColorAt(point);
    EXPECT_TRUE(result == black);

    point = Point(-1, 0, 0);
    result = pattern.getColorAt(point);
    EXPECT_TRUE(result == black);

    point = Point(2, 0, 0);
    result = pattern.getColorAt(point);
    EXPECT_TRUE(result == white);
}