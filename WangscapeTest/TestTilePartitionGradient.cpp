#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../Wangscape/TilePartitionGradient.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WangscapeTest
{
    TEST_CLASS(TestTilePartitionGradient)
    {
    public:
        TEST_METHOD(TestGradientWeight)
        {
            Assert::AreEqual(31, gradient_weight(0, 0, 0, 0, 31));
            Assert::AreEqual(0, gradient_weight(0, 0, 31, 0, 31));
            Assert::AreEqual(0, gradient_weight(0, 0, 0, 31, 31));
            Assert::AreEqual(0, gradient_weight(0, 0, 31, 31, 31));
        }

        TEST_METHOD(TestGradientPartition)
        {
            std::string filename("../Wangscape/example/example_options.json");
            const Options options(filename);
            TilePartition tp;
            tile_partition_gradient(tp, { "0","0","1","1" }, options);
            sf::Image mask = tp[0].first.copyToImage();
            //mask.saveToFile("temp.png");
            Assert::IsTrue(mask.getPixel(0, 0) == sf::Color(255, 255, 255, 255),
                           L"Mask 0: Wrong colour in top left pixel");
            Assert::IsTrue(mask.getPixel(0, 31) == sf::Color(255, 255, 255, 0),
                           L"Mask 0: Wrong colour in bottom left pixel");
            Assert::IsTrue(mask.getPixel(31, 0) == sf::Color(255, 255, 255, 0),
                           L"Mask 0: Wrong colour in top right pixel");
            Assert::IsTrue(mask.getPixel(31, 31) == sf::Color(255, 255, 255, 0),
                           L"Mask 0: Wrong colour in bottom right pixel");

            mask = tp[1].first.copyToImage();
            //mask.saveToFile("temp.png");
            Assert::IsTrue(mask.getPixel(0, 0) == sf::Color(255, 255, 255, 0),
                           L"Mask 1: Wrong colour in top left pixel");
            Assert::IsTrue(mask.getPixel(0, 31) == sf::Color(255, 255, 255, 255),
                           L"Mask 1: Wrong colour in bottom left pixel");
            Assert::IsTrue(mask.getPixel(31, 0) == sf::Color(255, 255, 255, 0),
                           L"Mask 1: Wrong colour in top right pixel");
            Assert::IsTrue(mask.getPixel(31, 31) == sf::Color(255, 255, 255, 0),
                           L"Mask 1: Wrong colour in bottom right pixel");

            mask = tp[2].first.copyToImage();
            //mask.saveToFile("temp.png");
            Assert::IsTrue(mask.getPixel(0, 0) == sf::Color(255, 255, 255, 0),
                           L"Mask 2: Wrong colour in top left pixel");
            Assert::IsTrue(mask.getPixel(0, 31) == sf::Color(255, 255, 255, 0),
                           L"Mask 2: Wrong colour in bottom left pixel");
            Assert::IsTrue(mask.getPixel(31, 0) == sf::Color(255, 255, 255, 255),
                           L"Mask 2: Wrong colour in top right pixel");
            Assert::IsTrue(mask.getPixel(31, 31) == sf::Color(255, 255, 255, 0),
                           L"Mask 2: Wrong colour in bottom right pixel");

            mask = tp[3].first.copyToImage();
            //mask.saveToFile("temp.png");
            Assert::IsTrue(mask.getPixel(0, 0) == sf::Color(255, 255, 255, 0),
                           L"Mask 3: Wrong colour in top left pixel");
            Assert::IsTrue(mask.getPixel(0, 31) == sf::Color(255, 255, 255, 0),
                           L"Mask 3: Wrong colour in bottom left pixel");
            Assert::IsTrue(mask.getPixel(31, 0) == sf::Color(255, 255, 255, 0),
                           L"Mask 3: Wrong colour in top right pixel");
            Assert::IsTrue(mask.getPixel(31, 31) == sf::Color(255, 255, 255, 255),
                           L"Mask 3: Wrong colour in bottom right pixel");
        }

    };
}