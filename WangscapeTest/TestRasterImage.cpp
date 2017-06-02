#include <gtest/gtest.h>

#include <noise/RasterImage.h>
#include <noise/module/WangscapeModules.h>
#include <SFML/System/Vector2.hpp>

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
    sf::Vector2u size(19, 21);
    image.create(size.x, size.y);
    noise::RasterImage ri(image, {0, 0, 1, 1}, constModule);
    EXPECT_EQ(size.x, ri.sizeX());
    EXPECT_EQ(size.y, ri.sizeY());
    EXPECT_EQ(0., ri.bounds().left);
    EXPECT_EQ(0., ri.bounds().top);
    EXPECT_EQ(1., ri.bounds().width);
    EXPECT_EQ(1., ri.bounds().height);
    for (size_t x = 0; x < size.x; x++)
    {
        for (size_t y = 0; y < size.y; y++)
        {
            EXPECT_EQ(0, ri.get(x, y).r);
            EXPECT_EQ(0, ri.get(x, y).g);
            EXPECT_EQ(0, ri.get(x, y).b);
        }
    }
}

TEST_F(TestRasterImage, TestRasterValuesOutOfRange)
{
    sf::Vector2u size(11, 9);
    image.create(size.x, size.y);
    noise::RasterImage ri(image, {0, 0, 1, 1}, constModule);
    EXPECT_ANY_THROW(ri.get(-1, -1););
    EXPECT_ANY_THROW(ri.get(0, -1););
    EXPECT_ANY_THROW(ri.get(size.x - 1, -1););
    EXPECT_ANY_THROW(ri.get(size.x, -1););

    EXPECT_ANY_THROW(ri.get(-1, 0););
    EXPECT_ANY_THROW(ri.get(size.x, 0););

    EXPECT_ANY_THROW(ri.get(-1, size.y - 1););
    EXPECT_ANY_THROW(ri.get(size.x, size.y - 1););

    EXPECT_ANY_THROW(ri.get(-1, size.y););
    EXPECT_ANY_THROW(ri.get(0, size.y););
    EXPECT_ANY_THROW(ri.get(size.x - 1, size.y););
    EXPECT_ANY_THROW(ri.get(size.x, size.y););
}

TEST_F(TestRasterImage, TestRasterValuesBuild)
{
    sf::Rect<double> bounds{-2, -2, 4, 4};

    const unsigned int size = 15;
    const unsigned int size_sub_1 = size - 1;
    const unsigned int almost_quarter_size = size_sub_1 / 4;
    const unsigned int size_1_2 = size / 2;
    // These must be closer to 0.0 than -2.0 or 2.0 in the raster rectangle.
    const unsigned int size_1_4 = size_1_2 - almost_quarter_size;  
    const unsigned int size_3_4 = size_1_2 + almost_quarter_size;

    image.create(size, size);
    noise::RasterImage ri(image, bounds);

    ri.build(gradientXModule);

    EXPECT_EQ(sf::Color::Green, ri.get(0, 0));
    EXPECT_EQ(sf::Color::Green, ri.get(0, size_sub_1));

    EXPECT_EQ(sf::Color::White, ri.get(size_sub_1, 0));
    EXPECT_EQ(sf::Color::White, ri.get(size_sub_1, size_sub_1));

    EXPECT_EQ(sf::Color::Black, ri.get(size_1_2, 0));
    EXPECT_EQ(sf::Color::Black, ri.get(size_1_2, size_sub_1));

    sf::Color c;
    c = ri.get(size_1_4, size_1_2);
    EXPECT_LT(128, c.r);
    EXPECT_EQ(0, c.g);
    EXPECT_EQ(0, c.b);

    c = ri.get(size_3_4, size_1_2);
    EXPECT_EQ(0, c.r);
    EXPECT_EQ(0, c.g);
    EXPECT_LT(128, c.b);

    ri.build(gradientYModule);

    EXPECT_EQ(sf::Color::Green, ri.get(0, 0));
    EXPECT_EQ(sf::Color::Green, ri.get(size_sub_1, 0));

    EXPECT_EQ(sf::Color::White, ri.get(0, size_sub_1));
    EXPECT_EQ(sf::Color::White, ri.get(size_sub_1, size_sub_1));

    EXPECT_EQ(sf::Color::Black, ri.get(0, size_1_2));
    EXPECT_EQ(sf::Color::Black, ri.get(size_sub_1, size_1_2));

    c = ri.get(size_1_2, size_1_4);
    EXPECT_LT(128, c.r);
    EXPECT_EQ(0, c.g);
    EXPECT_EQ(0, c.b);

    c = ri.get(size_1_2, size_3_4);
    EXPECT_EQ(0, c.r);
    EXPECT_EQ(0, c.g);
    EXPECT_LT(128, c.b);

}