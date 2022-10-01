#include <gtest/gtest.h>
#include "scene/world.h"

TEST(SceneTest, creation) {
    World world{};
    EXPECT_EQ(world.objects().size(), 0);
}

TEST(SceneTest, defaultWorld) {
    Tuple position(1.0, 1.0, 1.0);
    Color color(1.0, 1.0, 1.0);
    PointLight light(color, position);
    std::vector<PointLight> pointLights;
    pointLights.push_back(light);

    std::vector<Shape *> shapes;
    std::vector<DirectionalLight> directLights;

    World world(shapes, directLights, pointLights);

    EXPECT_EQ(world.pointLights().size() , 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}