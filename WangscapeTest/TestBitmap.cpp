#include <gtest/gtest.h>
#include <noise/module/Bitmap.h>
#include <memory>
#include "TestRequiringOptions.h"

class TestBitmap : public TestRequiringOptions
{
protected:
    TestBitmap() :
        TestRequiringOptions()
    {}
    noise::module::Bitmap bitmap;
};

TEST_F(TestBitmap, TestBitmapValue)
{
    double infinity = std::numeric_limits<double>::infinity();
    bitmap.SetDefaultValue(infinity);
    bitmap.SetRegion(sf::Rect<double>(-1., -1., 2., 2.));
    bitmap.SetFilename("../../tests/bitmap.png");
    bitmap.SetMaxScale(false);
    EXPECT_EQ(0., bitmap.GetValue(0, 0, 0));

    EXPECT_EQ(0., bitmap.GetValue( 0.99,  0.99, 0.));
    EXPECT_EQ(0., bitmap.GetValue( 0.99, -0.99, 1.));
    EXPECT_EQ(0., bitmap.GetValue(-0.99,  0.99, 2.));
    EXPECT_EQ(0., bitmap.GetValue(-0.99, -0.99, 3.));

    EXPECT_EQ(255., bitmap.GetValue(-0.5, -0.5, 4.));
    EXPECT_EQ(128., bitmap.GetValue( 0.5, -0.5, 5.));
    EXPECT_EQ(64. , bitmap.GetValue(-0.5,  0.5, 6.));
    EXPECT_EQ(0.  , bitmap.GetValue( 0.5,  0.5, 7.));

    bitmap.SetMaxScale(true);
    EXPECT_EQ(1.,        bitmap.GetValue(-0.5, -0.5, 4.));
    EXPECT_EQ(128./255., bitmap.GetValue( 0.5, -0.5, 5.));
    EXPECT_EQ(64./255.,  bitmap.GetValue(-0.5,  0.5, 6.));
    EXPECT_EQ(0.,        bitmap.GetValue( 0.5,  0.5, 7.));

    EXPECT_EQ(infinity, bitmap.GetValue(-3., 0., 0.));
    EXPECT_EQ(infinity, bitmap.GetValue(5., 0., 0.));
    EXPECT_EQ(infinity, bitmap.GetValue(0., -10., 0.));
    EXPECT_EQ(infinity, bitmap.GetValue(0., 1.01, 0.));
}