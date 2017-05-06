#include <gtest/gtest.h>
#include <algorithm>
#include <numeric>
#include <tilegen/alpha/CalculatorDither.h>
#include <boost/optional.hpp>

class TestCalculatorDither : public ::testing::Test
{
public:
    tilegen::alpha::CalculatorBase::Weights weight_examples;
    std::vector<tilegen::alpha::CalculatorDither> cds;
    tilegen::alpha::CalculatorDither& cd1;
    tilegen::alpha::CalculatorDither& cd2;
    tilegen::alpha::CalculatorDither& cd256;
    std::mt19937 rng;
    TestCalculatorDither() :
        weight_examples{0., 1., 5678.8765, -1.},
        cds(3),
        cd1(cds[0]),
        cd2(cds[1]),
        cd256(cds[2])
    {
        std::random_device rd;
        rng.seed(rd());
        cd1.power = 1;
        cd2.power = 2;
        cd256.power = 256;
    }
    static ptrdiff_t winnerIndex(const tilegen::alpha::CalculatorBase::Alphas& alphas)
    {
        return std::distance(alphas.cbegin(), std::max_element(alphas.cbegin(), alphas.cend()));
    }
    static void validateResult(tilegen::alpha::CalculatorDither& cd,
                               const tilegen::alpha::CalculatorBase::Weights& weights,
                               boost::optional<std::pair<double, double>> expected_values = boost::none,
                               boost::optional<size_t> expected_winners = 2)
    {
        std::set<ptrdiff_t> results;
        for (int i = 0; i < 256; i++)
        {
            cd.updateAlphas(weights);
            const auto& alphas = cd.getAlphas();
            ptrdiff_t winner_index = winnerIndex(alphas);
            results.insert(winner_index);
            if (expected_values)
            {
                EXPECT_TRUE(weights[winner_index] == expected_values->first ||
                            weights[winner_index] == expected_values->second);
            }
            for (size_t i = 0; i < alphas.size(); i++)
            {
                if (i == winner_index)
                    EXPECT_EQ(255, alphas[i]);
                else
                    EXPECT_EQ(0, alphas[i]);
            }
        }
        if (expected_winners)
        {
            if (cd.power < 10)
                EXPECT_EQ(expected_winners, results.size()) <<
                "Unexpected number of winners. power = " << std::to_string(cd.power);
            else // Dither behaviour for power==256 is very different from power==2 or 1.
                EXPECT_EQ(1, results.size()) <<
                "Unexpected number of winners. power = " << std::to_string(cd.power);
        }
    }
};

TEST_F(TestCalculatorDither, TestCalculatorDitherAllEqual)
{
    for (double weight : weight_examples)
    {
        tilegen::alpha::CalculatorBase::Weights weights{weight, weight, weight, weight};
        for (auto& cd : cds)
        {
            validateResult(cd, weights, std::make_pair(weight, weight), 1);
        }
    }
}

TEST_F(TestCalculatorDither, TestCalculatorDitherThreeEqual)
{
    size_t count = 0;
    for (double weight : weight_examples)
    {
        tilegen::alpha::CalculatorBase::Weights weights{weight, weight, weight, weight};
        weights[count%weights.size()] = -20.;
        for (auto& cd : cds)
        {
            validateResult(cd, weights, std::make_pair(weight, weight), 1);
        }
        count++;
    }
}

TEST_F(TestCalculatorDither, TestCalculatorDitherWinnerEqual)
{
    size_t count = 0;
    for (double weight : weight_examples)
    {
        tilegen::alpha::CalculatorBase::Weights weights{weight, weight, weight - 1, weight - 50};
        std::shuffle(weights.begin(), weights.end(), rng);
        for (auto& cd : cds)
        {
            validateResult(cd, weights, std::make_pair(weight, weight), 1);
        }
        count++;
    }
}

TEST_F(TestCalculatorDither, TestCalculatorDitherRunnerUpEqual)
{
    size_t count = 0;
    for (double weight : weight_examples)
    {
        tilegen::alpha::CalculatorBase::Weights weights{weight, weight - 1, weight - 1, weight - 50};
        std::shuffle(weights.begin(), weights.end(), rng);
        for (auto& cd : cds)
        {
            validateResult(cd, weights, std::make_pair(weight, weight-1), 1);
        }
        count++;
    }
}

TEST_F(TestCalculatorDither, TestCalculatorDitherAllDifferent)
{
    for (double weight : weight_examples)
    {
        double weight_runner_up = weight - (2. / 3.);
        tilegen::alpha::CalculatorBase::Weights weights{weight, weight_runner_up, weight - 1, weight - 50};
        std::shuffle(weights.begin(), weights.end(), rng);

        validateResult(cd1, weights, std::make_pair(weight, weight_runner_up));
        validateResult(cd2, weights, std::make_pair(weight, weight_runner_up));
        validateResult(cd256, weights, std::make_pair(weight, weight));
    }
}

TEST_F(TestCalculatorDither, TestCalculatorDitherRandom)
{
    std::uniform_real_distribution<double> weight_gen(-10, 10);
    for (int i = 0; i<20; i++)
    {
        for (auto& cd : cds)
        {
            tilegen::alpha::CalculatorBase::Weights weights{
                weight_gen(rng), weight_gen(rng),
                weight_gen(rng), weight_gen(rng)};
            std::shuffle(weights.begin(), weights.end(), rng);

            validateResult(cd, weights, boost::none, boost::none);
        }
    }
}
