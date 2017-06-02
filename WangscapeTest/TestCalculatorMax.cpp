#include <gtest/gtest.h>
#include <random>
#include <numeric>
#include <algorithm>

#include <tilegen/alpha/CalculatorMax.h>

class TestCalculatorMax : public ::testing::Test
{
public:
    tilegen::alpha::CalculatorMax cm;
    std::mt19937 rng;
    TestCalculatorMax()
    {
        std::random_device rd;
        rng.seed(rd());
    }
    int countValue(const tilegen::alpha::CalculatorBase::Alphas& alphas, int value)
    {
        return std::count(alphas.cbegin(), alphas.cend(), value);
    }
    ptrdiff_t validateResults(const tilegen::alpha::CalculatorBase::Weights& weights)
    {
        cm.updateAlphas(weights);
        const auto& alphas = cm.getAlphas();
        EXPECT_EQ(3, countValue(alphas, 0));
        EXPECT_EQ(1, countValue(alphas, 255));
        ptrdiff_t winner_index = std::distance(alphas.cbegin(), std::max_element(alphas.cbegin(), alphas.cend()));
        double max_value = *std::max_element(weights.cbegin(), weights.cend());
        EXPECT_EQ(max_value, weights[winner_index]);
        return winner_index;
    }
};



TEST_F(TestCalculatorMax, TestCalculatorMaxDeterministic)
{
    validateResults({0., 0., 0., 0.});

    EXPECT_EQ(0, validateResults({1., 0., 0., 0.}));
    EXPECT_EQ(1, validateResults({0., 1., 0., 0.}));
    EXPECT_EQ(2, validateResults({0., 0., 1., 0.}));
    EXPECT_EQ(3, validateResults({0., 0., 0., 1.}));

    validateResults({0., 1., 1., 0.});
    validateResults({1., 0., 1., 1.});
    validateResults({1., 1., 1., 1.});
}

TEST_F(TestCalculatorMax, TestCalculatorMaxRandom)
{
    tilegen::alpha::CalculatorBase::Weights weights(4);
    std::uniform_real_distribution<double> weight_gen(-10, 10);
    for (int i = 0; i < 100; i++)
    {
        for (auto& w : weights)
        {
            w = weight_gen(rng);
        }
        validateResults(weights);
    }
}

TEST_F(TestCalculatorMax, TestCalculatorMaxRandomBiased)
{
    tilegen::alpha::CalculatorBase::Weights weights(4);
    std::uniform_real_distribution<double> weight_gen(-10, 10);
    for (int i = 0; i < 1000; i++)
    {
        for (auto& w : weights)
        {
            w = weight_gen(rng);
        }
        size_t slot = i % weights.size();
        weights[slot] += 40.;
        EXPECT_EQ(slot, validateResults(weights));
    }
}