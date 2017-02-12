#include <gtest/gtest.h>

#include <type_traits>
#include <algorithm>
#include <tuple>

#include <noise/noise.h>
#include <noise/EncodedModuleGroup.h>

template<typename T>
class TestModuleDecode : public ::testing::Test
{
public:
    TestModuleDecode()
    {
    }
};

typedef ::testing::Types<
    noise::module::Abs,
    noise::module::Add
>
ModuleDecodeArgs;

TYPED_TEST_CASE(TestModuleDecode, ModuleDecodeArgs);

TYPED_TEST(TestModuleDecode, TestModuleDecode)
{

}
