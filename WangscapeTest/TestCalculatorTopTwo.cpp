#include <gtest/gtest.h>

#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <random>

#include <tilegen/alpha/CalculatorTopTwo.h>

class TestCalculatorTopTwo : public ::testing::Test
{
public:
    tilegen::alpha::CalculatorBase::Weights weight_examples;
    std::vector<tilegen::alpha::CalculatorTopTwo> ctts;
    tilegen::alpha::CalculatorTopTwo& ctt1;
    tilegen::alpha::CalculatorTopTwo& ctt2;
    tilegen::alpha::CalculatorTopTwo& ctt256;
    std::mt19937 rng;
    TestCalculatorTopTwo() :
        weight_examples{0., 1., 5678.8765, -1.},
        ctts(3),
        ctt1(ctts[0]),
        ctt2(ctts[1]),
        ctt256(ctts[2])
    {
        std::random_device rd;
        rng.seed(rd());
        ctt1.power = 1;
        ctt2.power = 2;
        ctt256.power = 256;
    }
};

TEST_F(TestCalculatorTopTwo, TestCalculatorTopTwoAllEqual)
{
    for (double weight : weight_examples)
    {
        tilegen::alpha::CalculatorBase::Weights weights{weight, weight, weight, weight};
        for (auto& ctt : ctts)
        {
            ctt.updateAlphas(weights);
            const auto& alphas = ctt.getAlphas();
            EXPECT_EQ(128, alphas[3]);
            EXPECT_EQ(127, alphas[2]);
            EXPECT_EQ(255, std::accumulate(alphas.cbegin(), alphas.cend(), 0));
        }
    }
}

TEST_F(TestCalculatorTopTwo, TestCalculatorTopTwoThreeEqual)
{
    size_t count = 0;
    for (double weight : weight_examples)
    {
        tilegen::alpha::CalculatorBase::Weights weights{weight, weight, weight, weight};
        weights[count%weights.size()] = -20.;
        for (auto& ctt : ctts)
        {
            ctt.updateAlphas(weights);
            const auto& alphas = ctt.getAlphas();
            EXPECT_TRUE(std::any_of(alphas.cbegin(), alphas.cend(), [](sf::Uint8 x) {return x == 128; }));
            EXPECT_TRUE(std::any_of(alphas.cbegin(), alphas.cend(), [](sf::Uint8 x) {return x == 127; }));
            EXPECT_EQ(255, std::accumulate(alphas.cbegin(), alphas.cend(), 0));
        }
        count++;
    }
}

TEST_F(TestCalculatorTopTwo, TestCalculatorTopTwoWinnerEqual)
{
    size_t count = 0;
    for (double weight : weight_examples)
    {
        tilegen::alpha::CalculatorBase::Weights weights{weight, weight, weight-1, weight-50};
        std::shuffle(weights.begin(), weights.end(), rng);
        for (auto& ctt : ctts)
        {
            ctt.updateAlphas(weights);
            const auto& alphas = ctt.getAlphas();
            EXPECT_TRUE(std::any_of(alphas.cbegin(), alphas.cend(), [](sf::Uint8 x) {return x == 128; }));
            EXPECT_TRUE(std::any_of(alphas.cbegin(), alphas.cend(), [](sf::Uint8 x) {return x == 127; }));
            EXPECT_EQ(255, std::accumulate(alphas.cbegin(), alphas.cend(), 0));
        }
        count++;
    }
}

TEST_F(TestCalculatorTopTwo, TestCalculatorTopTwoRunnerUpEqual)
{
    size_t count = 0;
    for (double weight : weight_examples)
    {
        tilegen::alpha::CalculatorBase::Weights weights{weight, weight - 1, weight - 1, weight - 50};
        std::shuffle(weights.begin(), weights.end(), rng);
        for (auto& ctt : ctts)
        {
            ctt.updateAlphas(weights);
            const auto& alphas = ctt.getAlphas();
            auto max_it = std::find(weights.cbegin(), weights.cend(), weight);
            ptrdiff_t max_index = std::distance(weights.cbegin(), max_it);
            EXPECT_EQ(255, alphas[max_index]);
            EXPECT_EQ(255, std::accumulate(alphas.cbegin(), alphas.cend(), 0));
        }
        count++;
    }
}

TEST_F(TestCalculatorTopTwo, TestCalculatorTopTwoAllDifferent)
{
    for (double weight : weight_examples)
    {
        double weight_runner_up = weight - (2. / 3.);
        tilegen::alpha::CalculatorBase::Weights weights{weight, weight_runner_up, weight - 1, weight - 50};
        std::shuffle(weights.begin(), weights.end(), rng);
        ptrdiff_t winner_index = std::distance(weights.cbegin(), std::find(weights.cbegin(), weights.cend(), weight));
        ptrdiff_t runner_up_index = std::distance(weights.cbegin(), std::find(weights.cbegin(), weights.cend(), weight_runner_up));
        for (auto& ctt : ctts)
        {
            ctt.updateAlphas(weights);
            const auto& alphas = ctt.getAlphas();
            EXPECT_EQ(255, std::accumulate(alphas.cbegin(), alphas.cend(), 0));
        }
        {
            const auto& alphas = ctt1.getAlphas();
            EXPECT_NEAR(192, alphas[winner_index],2);
            EXPECT_NEAR(64, alphas[runner_up_index], 2);
        }
        {
            const auto& alphas = ctt2.getAlphas();
            EXPECT_NEAR(230, alphas[winner_index], 2);
            EXPECT_NEAR(26, alphas[runner_up_index], 2);
        }
        {
            const auto& alphas = ctt256.getAlphas();
            EXPECT_NEAR(254, alphas[winner_index], 1);
            EXPECT_NEAR(1, alphas[runner_up_index], 1);
        }
    }
}

TEST_F(TestCalculatorTopTwo, TestCalculatorTopTwoRandom)
{
    std::uniform_real_distribution<double> weight_gen(-10, 10);
    for(int i=0; i<100; i++)
    {
        for (auto& ctt : ctts)
        {
            tilegen::alpha::CalculatorBase::Weights weights{
                weight_gen(rng), weight_gen(rng),
                weight_gen(rng), weight_gen(rng)};
            std::shuffle(weights.begin(), weights.end(), rng);
            ptrdiff_t winner_index = std::distance(weights.cbegin(), std::max_element(weights.cbegin(), weights.cend()));
            ctt.updateAlphas(weights);
            const auto& alphas = ctt.getAlphas();
            EXPECT_EQ(255, std::accumulate(alphas.cbegin(), alphas.cend(), 0));
            EXPECT_LE(128, alphas[winner_index]);
            EXPECT_LE(2, std::accumulate(
                alphas.cbegin(), alphas.cend(), 0,
                [](int acc, sf::Uint8 x)
            { return (x == 0) ? acc + 1 : acc; }));
        }
    }
}
