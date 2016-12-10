#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../Wangscape/Options.h"
#include "../Wangscape/TilesetGenerator.h"
#include <SFML/Graphics.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WangscapeTest
{
    TEST_CLASS(TestMetaOutput)
    {
    public:

        TEST_METHOD(TestMetaOutputCorrect)
        {
            std::string filename("../Wangscape/example/example_options.json");
            const Options options(filename);
            TilesetGenerator tg(options);
            tg.generate([&](const sf::Texture& output, std::string filename){});
            const auto& td = tg.mo.getTileData();
            // A lot of tests are not implemented because they are better situated in JSON schema validation.
            {
                Assert::IsTrue(td.IsArray(), L"TileData is not an array");
                const auto& td_item = td[0];
                Assert::IsTrue(td_item.IsObject(), L"TileData[0] is not an object");
                Assert::IsTrue(td_item.HasMember("corners"), L"TileData[0] does not have corners");
                const auto& td_item_corners = (*td_item.FindMember("corners")).value;
                Assert::IsTrue(td_item_corners.IsArray(), L"TileData[0][""corners""] is not an array");
                for (int i = 0; i < 4; i++)
                    Assert::AreEqual(td_item_corners[i].GetString(), "g", L"Incorrect terrain id in TileData[0][""corners""]");
            }
            {
                const auto& td_item = td[15];
                Assert::IsTrue(td_item.IsObject(), L"TileData[15] is not an object");
                Assert::IsTrue(td_item.HasMember("corners"), L"TileData[15] does not have corners");
                const auto& td_item_corners = (*td_item.FindMember("corners")).value;
                Assert::IsTrue(td_item_corners.IsArray(), L"TileData[15][""corners""] is not an array");
                for (int i = 0; i < 4; i++)
                    Assert::AreEqual(td_item_corners[i].GetString(), "s", L"Incorrect terrain id in TileData[0][""corners""]");

                const auto& tsd = tg.mo.getTilesetData();
                //Assert::IsTrue(tsd.IsObject());
                Assert::IsTrue(tsd.HasMember("g.s.png"));
            }
        }
    };
}