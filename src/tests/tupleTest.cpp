#include <iostream>
#include <gtest/gtest.h>
#include "primitives/math.h"
#include "primitives/tuple.h"

TEST(TupleTest, simpleSum) {
    Tuple tuple = Point(1.0, 1.0, 1.0);
    Tuple tuple2 = Vector(1.0, 1.0, 1.0);

    Tuple result = tuple + tuple2;

    EXPECT_FLOAT_EQ(result.x, 2.0);
    EXPECT_FLOAT_EQ(result.y, 2.0);
    EXPECT_FLOAT_EQ(result.z, 2.0);

    EXPECT_TRUE(tuple.isPoint());
}

TEST(TupleTest, simpleNegation) {
    Tuple tuple = Point(1.0, 1.0, 1.0);
    tuple = -tuple;

    EXPECT_TRUE(epsilon_eq(tuple.x, -1.0));
    EXPECT_TRUE(epsilon_eq(tuple.y, -1.0));
    EXPECT_TRUE(epsilon_eq(tuple.z, -1.0));
    EXPECT_TRUE(epsilon_eq(tuple.w, -1.0));
}

TEST(TupleTest, simpleNormalize) {
    Tuple tuple = Tuple(10.0, 10.0, 10.0, 10.0);

    float magnitude = tuple.magnitude();
    Tuple result = tuple.normalized();

    EXPECT_TRUE(epsilon_eq(result.x, tuple.x / magnitude));
    EXPECT_TRUE(epsilon_eq(result.y, tuple.y / magnitude));
    EXPECT_TRUE(epsilon_eq(result.z, tuple.z / magnitude));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}