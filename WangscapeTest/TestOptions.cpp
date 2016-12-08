#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <fstream>
#include <sstream>
#include <istream>
#include "../Wangscape/Options.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WangscapeTest
{
	TEST_CLASS(TestOptions)
	{
	public:
        TEST_METHOD(TestOptionsButDont)
        {
            Assert::IsTrue(false, L"JSON options documents are not currently tested.");
        }
        TEST_METHOD(TestOptionsParse)
        {
            std::string filename("../Wangscape/example/example_options.json");
            std::ifstream ifs(filename);
            Assert::IsTrue(ifs.good(),L"Couldn't open example json options");
            rapidjson::IStreamWrapper isw(ifs);
            rapidjson::Document options_document;
            options_document.ParseStream(isw);
            if (options_document.HasParseError())
            {
                std::wstringstream ss;
                ss << "Options document has parse error at offset " << (unsigned)options_document.GetErrorOffset() << ":\n";
                ss << GetParseError_En(options_document.GetParseError()) << "\n";
                Assert::IsFalse(options_document.HasParseError(), ss.str().c_str());
            }
            const Options options(options_document, filename);
        }
        // JSON validation with schemas in C++ is a complete mess.
        // rapidjson crashes when using valid schemas to validate conforming documents.
        // rapidjson wrapped by valijson fails in the same place.
        // picojson wrapped by valijson fails in the same place (and needs #define PICOJSON_USE_INT64 true).
        // External tools like jsonlint are available, but I do not want to spend PROCJAM figuring out system/ShellExecute APIs.
        // JSON option document validity and conformity can be tested after these libraries are fixed.
        // In the meantime, the schema and example documents can be validated manually with external tools.
	};
}