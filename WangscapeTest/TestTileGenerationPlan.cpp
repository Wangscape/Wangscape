#include <gtest/gtest.h>

#include <MakeReseedable.h>
#include <ModuleFactories.h>
#include <NoiseMap.h>

class TestTileGenerationPlan : public ::testing::Test {
protected:
    Reseedable x;
    Reseedable y;
    TestTileGenerationPlan() :
        x(makeX()),
        y(makeY())
    {
    };
    ~TestTileGenerationPlan() {};
};

TEST_F(TestTileGenerationPlan, TestTileGenerationPlan)
{
    sf::Image output;
    output.create(256, 256);

    NoiseMapBase::Bounds xy(0, 0, 1, 1);
    NoiseMapBase::Bounds xy_(0, -1, 1, 1);
    NoiseMapBase::Bounds x_y(-1, 0, 1, 1);
    NoiseMapBase::Bounds x_y_(-1, -1, 1, 1);

    NoiseMapImage nmixy(output, xy);
    NoiseMapImage nmixy_(output, xy_);
    NoiseMapImage nmix_y(output, x_y);
    NoiseMapImage nmix_y_(output, x_y_);

    auto write_map = [&](const Reseedable module,
                        std::string filename,
                        NoiseMapImage& nmi)
    {
        nmi.build(*module.module);
        output.saveToFile("test/"+filename+".png");
    };

    write_map(x, "x", nmixy);
    write_map(x, "x_", nmix_y);
    write_map(y, "y", nmixy);
    write_map(y, "y_", nmixy_);
    
    Reseedable stochastic = makePlaceholder(259738);
    Reseedable border_x = makePlaceholder(5204790);
    Reseedable border_y = makePlaceholder(923784);

    write_map(stochastic, "stochastic", nmixy);
    write_map(border_x, "border_x", nmixy);
    write_map(border_x, "border_x_", nmix_y);
    write_map(border_y, "border_y", nmixy);
    write_map(border_y, "border_y_", nmixy_);

    Reseedable msb_x = makeLinearMovingScaleBias(y, true, 0.8, 0.3);
    Reseedable msb_y = makeLinearMovingScaleBias(x, false, 0.8, 0.3);
    write_map(msb_x, "msb_x", nmixy);
    write_map(msb_y, "msb_y", nmixy);

    Reseedable msb_bx = makeLinearMovingScaleBias(border_x, true, 0.8, 0.3);
    Reseedable msb_by = makeLinearMovingScaleBias(border_y, false, 0.8, 0.3);
    write_map(msb_bx, "msb_bx", nmixy);
    write_map(msb_bx, "msb_bx_", nmix_y);
    write_map(msb_by, "msb_by", nmixy);
    write_map(msb_by, "msb_by_", nmixy_);

}
