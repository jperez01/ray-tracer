#include <iostream>
#include <gtest/gtest.h>
#include "primitives/color.h"

TEST(ColorTest, simpleMult) {
    Color red = Color(1.0, 0.0, 0.0);
    Color blue = Color(0.0, 0.0, 1.0);

    Color product = red * blue;

    EXPECT_FLOAT_EQ(product.r(), 0.0);
    EXPECT_FLOAT_EQ(product.g(), 0.0);
    EXPECT_FLOAT_EQ(product.b(), 0.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}