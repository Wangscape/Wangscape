#include <gtest/gtest.h>
#include <random>
#include <numeric>
#include <algorithm>

#include <tilegen/alpha/CalculatorLinear.h>

class TestCalculatorLinear : public ::testing::Test
{
public:
    tilegen::alpha::CalculatorLinear cl;
    std::mt19937 rng;
    TestCalculatorLinear()
    {
        std::random_device rd;
        rng.seed(rd());
    }
    ptrdiff_t validateResults(const tilegen::alpha::CalculatorBase::Weights& weights)
    {
        cl.updateAlphas(weights);
        const auto& alphas = cl.getAlphas();
        int total_alpha = std::accumulate(alphas.cbegin(), alphas.cend(), 0);
        EXPECT_EQ(255, total_alpha);
        double total_weight = std::accumulate(weights.cbegin(), weights.cend(), 0.);
        for (size_t i = 0; i < 4; i++)
        {
            double alpha_fraction = alphas[i];
            double weight_fraction = double(weights[i]) * total_alpha / total_weight;
            // Maximum absolute error is 0.5 from integer quantisation plus 1.0 from distribution of remainder.
            EXPECT_NEAR(alpha_fraction, weight_fraction, 1.5);
        }
        ptrdiff_t winner_index = std::distance(alphas.cbegin(), std::max_element(alphas.cbegin(), alphas.cend()));
        return winner_index;
    }
};

TEST_F(TestCalculatorLinear, TestCalculatorLinearDeterministic)
{
    EXPECT_EQ(0, validateResults({1., 0., 0., 0.}));
    EXPECT_EQ(255, cl.getAlphas()[0]);

    EXPECT_EQ(1, validateResults({0., 2., 0., 0.}));
    EXPECT_EQ(255, cl.getAlphas()[1]);

    EXPECT_EQ(2, validateResults({0., 0., 3., 0.}));
    EXPECT_EQ(255, cl.getAlphas()[2]);

    EXPECT_EQ(3, validateResults({0., 0., 0., 4.}));
    EXPECT_EQ(255, cl.getAlphas()[3]);

    validateResults({0., 1., 1., 0.});
    EXPECT_TRUE(cl.getAlphas()[1] == 128 || cl.getAlphas()[1] == 127);
    EXPECT_TRUE(cl.getAlphas()[2] == 128 || cl.getAlphas()[2] == 127);

    validateResults({1., 0., 1., 1.});
    EXPECT_EQ(85, cl.getAlphas()[0]);
    EXPECT_EQ(85, cl.getAlphas()[2]);
    EXPECT_EQ(85, cl.getAlphas()[3]);

    validateResults({1., 1., 1., 1.});
    for(int i=0; i < 4; i++)
        EXPECT_TRUE(cl.getAlphas()[i] == 64 || cl.getAlphas()[i] == 63);
}

TEST_F(TestCalculatorLinear, TestCalculatorLinearRandom)
{
    tilegen::alpha::CalculatorBase::Weights weights(4);
    std::uniform_real_distribution<double> weight_gen(0.001, 10.);
    for (int i = 0; i < 100; i++)
    {
        for (tilegen::alpha::CalculatorBase::Weights::value_type& w : weights)
        {
            w = weight_gen(rng);
        }
        validateResults(weights);
    }
}

TEST_F(TestCalculatorLinear, TestCalculatorLinearRandomBiased)
{
    tilegen::alpha::CalculatorBase::Weights weights(4);
    std::uniform_real_distribution<double> weight_gen(0., 10.);
    for (int i = 0; i < 1000; i++)
    {
        for (tilegen::alpha::CalculatorBase::Weights::value_type& w : weights)
        {
            w = weight_gen(rng);
        }
        size_t slot = i % weights.size();
        weights[slot] += 20.;
        EXPECT_EQ(slot, validateResults(weights));
        EXPECT_LE(101, cl.getAlphas()[slot]);
    }
}
