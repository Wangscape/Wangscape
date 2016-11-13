#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

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
        // JSON validation with schemas in C++ is a complete mess.
        // rapidjson crashes when using valid schemas to validate conforming documents.
        // rapidjson wrapped by valijson fails in the same place.
        // picojson wrapped by valijson fails in the same place (and needs #define PICOJSON_USE_INT64 true).
        // External tools like jsonlint are available, but I do not want to spend PROCJAM figuring out system/ShellExecute APIs.
        // JSON option document validity and conformity can be tested after these libraries are fixed.
        // In the meantime, the schema and example documents can be validated manually with external tools.
	};
}