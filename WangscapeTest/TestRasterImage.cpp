#include <gtest/gtest.h>

#include <noise/RasterImage.h>
#include <noise/module/WangscapeModules.h>

class TestRasterImage : public ::testing::Test
{
protected:
    noise::module::GradientX gradientXModule;
    noise::module::GradientY gradientYModule;
    noise::module::Const constModule;
    sf::Image image;
    TestRasterImage()
    {
        constModule.SetConstValue(0.);
    };
};

TEST_F(TestRasterImage, TestRasterImageGetInBounds)
{
    image.create(20, 20);
    noise::RasterImage ri(image, {0, 0, 1, 1}, constModule);
    EXPECT_EQ(20, ri.sizeX());
    EXPECT_EQ(20, ri.sizeY());
    EXPECT_EQ(0., ri.bounds().left);
    EXPECT_EQ(0., ri.bounds().top);
    EXPECT_EQ(1., ri.bounds().width);
    EXPECT_EQ(1., ri.bounds().height);
    for (size_t x = 0; x < 20; x++)
    {
        for (size_t y = 0; y < 20; y++)
        {
            EXPECT_EQ(0, ri.get(x, y).r);
            EXPECT_EQ(0, ri.get(x, y).g);
            EXPECT_EQ(0, ri.get(x, y).b);
        }
    }
}

TEST_F(TestRasterImage, TestRasterValuesOutOfRange)
{
    image.create(10, 10);
    noise::RasterImage ri(image, {0, 0, 1, 1}, constModule);
    EXPECT_ANY_THROW(ri.get(-1, -1););
    EXPECT_ANY_THROW(ri.get(0, -1););
    EXPECT_ANY_THROW(ri.get(9, -1););
    EXPECT_ANY_THROW(ri.get(10, -1););

    EXPECT_ANY_THROW(ri.get(-1, 0););
    EXPECT_ANY_THROW(ri.get(10, 0););

    EXPECT_ANY_THROW(ri.get(-1, 9););
    EXPECT_ANY_THROW(ri.get(10, 9););

    EXPECT_ANY_THROW(ri.get(-1, 10););
    EXPECT_ANY_THROW(ri.get(0, 10););
    EXPECT_ANY_THROW(ri.get(9, 10););
    EXPECT_ANY_THROW(ri.get(10, 10););
}

TEST_F(TestRasterImage, TestRasterValuesBuild)
{
    image.create(15, 15);
    noise::RasterImage ri(image, {-2, -2, 4, 4});

    ri.build(gradientXModule);

    EXPECT_EQ(sf::Color::Green, ri.get(0, 0));
    EXPECT_EQ(sf::Color::Green, ri.get(0, 14));

    EXPECT_EQ(sf::Color::White, ri.get(14, 0));
    EXPECT_EQ(sf::Color::White, ri.get(14, 14));

    EXPECT_EQ(sf::Color::Black, ri.get(7, 0));
    EXPECT_EQ(sf::Color::Black, ri.get(7, 14));

    EXPECT_LT(128, ri.get(4, 7).r);
    EXPECT_EQ(0, ri.get(4, 7).g);
    EXPECT_EQ(0, ri.get(4, 7).b);

    EXPECT_EQ(0, ri.get(10, 7).r);
    EXPECT_EQ(0, ri.get(10, 7).g);
    EXPECT_LT(128, ri.get(10, 7).b);

    ri.build(gradientYModule);

    EXPECT_EQ(sf::Color::Green, ri.get(0, 0));
    EXPECT_EQ(sf::Color::Green, ri.get(14, 0));

    EXPECT_EQ(sf::Color::White, ri.get(0, 14));
    EXPECT_EQ(sf::Color::White, ri.get(14, 14));

    EXPECT_EQ(sf::Color::Black, ri.get(0, 7));
    EXPECT_EQ(sf::Color::Black, ri.get(14, 7));

    EXPECT_LT(128, ri.get(7, 4).r);
    EXPECT_EQ(0, ri.get(7, 4).g);
    EXPECT_EQ(0, ri.get(7, 4).b);

    EXPECT_EQ(0, ri.get(7, 10).r);
    EXPECT_EQ(0, ri.get(7, 10).g);
    EXPECT_LT(128, ri.get(7, 10).b);

}