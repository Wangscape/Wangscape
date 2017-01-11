#include <gtest/gtest.h>

#include <noise/module/Reseedable.h>
#include <noise/module/ReseedablePtr.h>

class TestReseedable : public ::testing::Test {
protected:
    noise::module::ReseedablePtr rp;
    noise::module::Reseedable<noise::module::Perlin> rperlin;
    noise::module::Reseedable<noise::module::Spheres> rspheres;
    TestReseedable()
    {
    };
    ~TestReseedable() {};
};
