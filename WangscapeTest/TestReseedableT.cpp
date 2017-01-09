#include <gtest/gtest.h>

#include <noise/module/ReseedableT.h>
#include <noise/module/ReseedablePtr.h>

class TestReseedable : public ::testing::Test {
protected:
    noise::module::ReseedablePtr rp;
    noise::module::ReseedableT<noise::module::Perlin> rperlin;
    noise::module::ReseedableT<noise::module::Spheres> rspheres;
    TestReseedable()
    {
    };
    ~TestReseedable() {};
};
