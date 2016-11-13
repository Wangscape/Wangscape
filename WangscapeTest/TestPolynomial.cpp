#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../Wangscape/Polynomial.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WangscapeTest
{		
	TEST_CLASS(TestPolynomial)
	{
	public:

		TEST_METHOD(TestConstantPolynomialEval)
		{
			Polynomial p({ 1 });
			Assert::AreEqual((Real)1.0f, p.evaluate(-1.0), (Real)0.0f);
			Assert::AreEqual((Real)1.0f, p.evaluate(0.0), (Real)0.0f);
			Assert::AreEqual((Real)1.0f, p.evaluate(1.0), (Real)0.0f);
		}
		TEST_METHOD(TestLinearPolynomialEval)
		{
			Polynomial p({ 1, 2 });
			Assert::AreEqual((Real)-1.0, p.evaluate(-1.0), (Real)0.0f);
			Assert::AreEqual((Real)1.0f, p.evaluate(0.0), (Real)0.0f);
			Assert::AreEqual((Real)3.0f, p.evaluate(1.0), (Real)0.0f);
		}

		TEST_METHOD(TestQuadraticPolynomialEval)
		{
			Polynomial p({ 1, 2, 3 });
			Assert::AreEqual((Real)2.0f, p.evaluate(-1.0), (Real)0.0f);
			Assert::AreEqual((Real)1.0f, p.evaluate(0.0), (Real)0.0f);
			Assert::AreEqual((Real)6.0f, p.evaluate(1.0), (Real)0.0f);
		}
		TEST_METHOD(TestCubicPolynomialEval)
		{
			Polynomial p({ 1, 2, 3, 4 });
			Assert::AreEqual((Real)-2.0f, p.evaluate(-1.0), (Real)0.0f);
			Assert::AreEqual((Real)1.0f, p.evaluate(0.0), (Real)0.0f);
			Assert::AreEqual((Real)10.0f, p.evaluate(1.0), (Real)0.0f);
		}
		TEST_METHOD(TestDerivative)
		{
			Polynomial p({ 2,3,5,7 });
			Polynomial d = p.makeDerivative();
			Assert::AreEqual((Real)3.f, d[0], (Real)0.0f);
			Assert::AreEqual((Real)10.f, d[1], (Real)0.0f);
			Assert::AreEqual((Real)21.f, d[2], (Real)0.0f);
		}
        TEST_METHOD(TestZeroDerivative)
        {
            Polynomial p({ 2 });
            Polynomial d = p.makeDerivative();
            Assert::IsTrue(d.is_zero());
        }
        TEST_METHOD(TestLinearSolutions)
        {
            Polynomial p({ 3,-4 });
            auto s = p.makeSolutions();
            Assert::AreEqual((size_t)1, s.size());
            Assert::AreEqual(0.75, s[0]);
        }
        TEST_METHOD(TestQuadraticSolutions)
        {
            Polynomial p1({ { 3., -4., 1. } });
            auto s = p1.makeSolutions();
            Assert::AreEqual((size_t)2, s.size());
            Real s1 = std::min(s[0],s[1]);
            Real s2 = std::max(s[0],s[1]);
            Assert::AreEqual(1.0, s1, 0.000001);
            Assert::AreEqual(3.0, s2, 0.000001);
            Polynomial p2({ { -3., -4., -1. } });
            s = p2.makeSolutions();
            Assert::AreEqual((size_t)2, s.size());
            s1 = std::min(s[0], s[1]);
            s2 = std::max(s[0], s[1]);
            Assert::AreEqual(-3.0, s1, 0.000001);
            Assert::AreEqual(-1.0, s2, 0.000001);
        }
        TEST_METHOD(TestQuadraticSolutionsAwkward)
        {
            Polynomial p({ 0.0001,1.,0.0001 });
            auto s = p.makeSolutions();
            Assert::AreEqual((size_t)2, s.size());
            Assert::AreEqual(0., p.evaluate(s[0]), 0.0001);
            Assert::AreEqual(0., p.evaluate(s[1]), 0.0001);
        }
	};
}