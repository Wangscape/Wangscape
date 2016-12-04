#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../Wangscape/Polynomial.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WangscapeTest
{
    TEST_CLASS(TestPolynomialAugmented)
    {
    public:

        TEST_METHOD(TestPolynomialAugmentedEvaluate)
        {
            PolynomialAugmented pa({ 1.,2.,3.,4. });
            const Polynomial& p = pa.polynomial();
            Assert::AreEqual((Real)-2.0f, p.evaluate(-1.0), (Real)0.0f);
            Assert::AreEqual((Real)1.0f, p.evaluate(0.0), (Real)0.0f);
            Assert::AreEqual((Real)10.0f, p.evaluate(1.0), (Real)0.0f);
        }
        TEST_METHOD(TestPolynomialAugmentedDerivative)
        {
            PolynomialAugmented pa({ 2,3,5,7 });
            const Polynomial& d = pa.derivative();
            Assert::AreEqual((Real)3.f, d[0], (Real)0.0f);
            Assert::AreEqual((Real)10.f, d[1], (Real)0.0f);
            Assert::AreEqual((Real)21.f, d[2], (Real)0.0f);
        }
        TEST_METHOD(TestPolynomialAugmentedExtrema)
        {
            PolynomialAugmented pa({ 3., -4., 1. });
            const PolynomialAugmented::Extrema& e = pa.extrema();
            Assert::AreEqual((size_t)1, e.size());
            Assert::AreEqual(2., e[0].first);
            Assert::AreEqual(-1., e[0].second);
        }
        TEST_METHOD(TestPolynomialAugmentedRange)
        {
            PolynomialAugmented pa({ 3., -4., 1. });
            const Interval I = pa.makeRange(Interval(1.5, 2.75));
            Assert::AreEqual(I.a, -1.);
            Assert::AreEqual(I.b, -0.4375);
        }

    };
}