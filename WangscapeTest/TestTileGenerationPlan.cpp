#include <gtest/gtest.h>

#include <MakeReseedable.h>
#include <ModuleFactories.h>
#include <NoiseMap.h>
#include <random>

class TestTileGenerationPlan : public ::testing::Test {
protected:
    Reseedable x;
    Reseedable y;
    Reseedable c0;
    Reseedable c1;
    TestTileGenerationPlan() :
        x(makeX()),
        y(makeY()),
        c0(makeConst(0)),
        c1(makeConst(1))
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

    Reseedable msb_max_xy = makeLinearMovingScaleBias(c1, true, true, 0.7, 0.25);
    Reseedable msb_max_xy_ = makeLinearMovingScaleBias(c1, true, false, 0.7, 0.25);
    Reseedable msb_max_x_y = makeLinearMovingScaleBias(c1, false, true, 0.7, 0.25);
    Reseedable msb_max_x_y_ = makeLinearMovingScaleBias(c1, false, false, 0.7, 0.25);
    Reseedable msb_min_xy = makeLinearMovingScaleBias(-c1, true, true, 0.7, 0.25);
    Reseedable msb_min_xy_ = makeLinearMovingScaleBias(-c1, true, false, 0.7, 0.25);
    Reseedable msb_min_x_y = makeLinearMovingScaleBias(-c1, false, true, 0.7, 0.25);
    Reseedable msb_min_x_y_ = makeLinearMovingScaleBias(-c1, false, false, 0.7, 0.25);

    write_map(msb_max_xy, "msb_max_xy", nmixy);
    write_map(msb_max_x_y, "msb_max_x_y", nmixy);
    write_map(msb_max_xy_, "msb_max_xy_", nmixy);
    write_map(msb_max_x_y_, "msb_max_x_y_", nmixy);
    write_map(msb_min_xy, "msb_min_xy", nmixy);
    write_map(msb_min_x_y, "msb_min_x_y", nmixy);
    write_map(msb_min_xy_, "msb_min_xy_", nmixy);
    write_map(msb_min_x_y_, "msb_min_x_y_", nmixy);

    Reseedable cc = makeCornerCombiner(true, true);
    write_map(cc, "ccxy", nmixy);
    write_map(cc, "ccxy_", nmixy_);
    write_map(cc, "ccx_y", nmix_y);
    write_map(cc, "ccx_y_", nmix_y_);

    std::mt19937 rng;
    rng.seed((unsigned int)time(nullptr));
    
    // this corner's weight in the tile centre
    Reseedable stochastic = makePlaceholder(rng()).scaleBias(0.5,0.5);
    // this corner's weight along its adjacent horizontal border
    Reseedable border_x = makePlaceholder(rng());
    // this corner's weight along its adjacent vertical border
    Reseedable border_y = makePlaceholder(rng());

    write_map(stochastic, "stochastic", nmixy);
    write_map(border_x, "borderx_y", nmixy);
    write_map(border_x, "borderx_y_", nmixy_);
    write_map(border_y, "bordery_x", nmixy);
    write_map(border_y, "bordery_x_", nmix_y);

    Reseedable border_xy = cc.blend(border_y, border_x);
    write_map(border_xy, "border_xy", nmixy);

    Reseedable deterministic = makeLinearMovingScaleBias(border_xy, true, true, 0.7, 0.25);
    write_map(deterministic, "deterministic", nmixy);

    Reseedable ef = makeEdgeFavouringMask(1.5, 1.);
    write_map(ef, "ef", nmixy);

    Reseedable corner = ef.blend(stochastic, deterministic);
    write_map(corner, "corner", nmixy);
}
