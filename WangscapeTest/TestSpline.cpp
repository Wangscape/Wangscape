#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../Wangscape/Spline.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WangscapeTest
{
    TEST_CLASS(TestSpline)
    {
    public:
        static Spline<2> s;
        TEST_METHOD_INITIALIZE(TestSplineSetup)
        {
            s = Spline<2>(-1.234, 1.534,
            { 123.543, 82.43 }, { 1490.23 ,-14.2 },
            { -987.3, 583.24 }, { 249.4, -593.3 });
        }
        TEST_METHOD(TestSplineValid)
        {
            Assert::IsTrue(s.valid());
        }
        TEST_METHOD(TestSplineAddExternal)
        {
            s.setKnot(10.52, { 529.6, -184.1 }, { 43.0, 0.0063 });
            Assert::IsTrue(s.valid());
        }
        TEST_METHOD(TestSplineAddInternal)
        {
            s.setKnot(0.52, { 529.6, -184.1 }, { 43.0, 0.0063 });
            Assert::IsTrue(s.valid());
        }
        TEST_METHOD(TestSplineAlterStartKnot)
        {
            s.setKnot(-10.52, { 529.6, -184.1 }, { 43.0, 0.0063 });
            s.setKnot(-10.52, { 0., 1. }, { 2., 3. });
            Assert::IsTrue(s.valid());
            Assert::AreEqual(0.0, s.evaluate(-10.52)[0]);
            Assert::AreEqual(1.0, s.evaluate(-10.52)[1]);
            Assert::AreEqual(2.0, s.derivative(-10.52)[0]);
            Assert::AreEqual(3.0, s.derivative(-10.52)[1]);

        }
        TEST_METHOD(TestSplineAlterMidKnot)
        {
            s.setKnot(0.52, { 529.6, -184.1 }, { 43.0, 0.0063 });
            s.setKnot(0.52, { 0., 1. }, { 2., 3. });
            Assert::IsTrue(s.valid());
            Assert::AreEqual(0.0, s.evaluate(0.52)[0]);
            Assert::AreEqual(1.0, s.evaluate(0.52)[1]);
            Assert::AreEqual(2.0, s.derivative(0.52)[0]);
            Assert::AreEqual(3.0, s.derivative(0.52)[1]);

        }
        TEST_METHOD(TestSplineAlterEndKnot)
        {
            s.setKnot(10.52, { 529.6, -184.1 }, { 43.0, 0.0063 });
            s.setKnot(10.52, { 0., 1. }, { 2., 3. });
            Assert::IsTrue(s.valid());
            Assert::AreEqual(0.0, s.evaluate(10.52)[0]);
            Assert::AreEqual(1.0, s.evaluate(10.52)[1]);
            Assert::AreEqual(2.0, s.derivative(10.52)[0]);
            Assert::AreEqual(3.0, s.derivative(10.52)[1]);
        }
        TEST_METHOD(TestSplineAlterValue)
        {
            Vector<2> original_derivative = s.derivative(0.52);
            s.setKnotValue(0.52, { 529.6, -184.1 });
            Vector<2> new_derivative = s.derivative(0.52);
            Assert::IsTrue(s.valid());
            Assert::IsTrue(almostEqual({ 529.6, -184.1 }, s.evaluate(0.52)));
            Assert::IsTrue(almostEqual(original_derivative, new_derivative));
        }
        TEST_METHOD(TestSplineAlterDerivative)
        {
            Vector<2> original_value = s.evaluate(0.52);
            s.setKnotDerivative(0.52, { 43.0, 0.0063 });
            Vector<2> new_value = s.evaluate(0.52);
            Assert::IsTrue(s.valid());
            Assert::IsTrue(almostEqual(original_value, new_value));
            Assert::IsTrue(almostEqual({ 43.0, 0.0063 }, s.derivative(0.52)));
        }
        TEST_METHOD(TestSplineAlterNothing)
        {
            Vector<2> original_value = s.evaluate(0.52);
            Vector<2> original_derivative = s.derivative(0.52);
            s.setKnotNoChange(0.52);
            Assert::IsTrue(s.valid());
            Assert::IsTrue(almostEqual(original_value, s.evaluate(0.52)));
            Assert::IsTrue(almostEqual(original_derivative, s.derivative(0.52)));
        }
        TEST_METHOD(TestSplineMinMax)
        {
            Assert::AreEqual(-1.234, s.tMin());
            Assert::AreEqual(1.534, s.tMax());
        }
        TEST_METHOD(TestSplineRemove)
        {
            s.setKnot(10.52, { 529.6, -184.1 }, { 43.0, 0.0063 });
            Assert::IsTrue(s.valid());
            s.removeKnot(-1.234);
            Assert::IsTrue(s.valid());
            Assert::AreEqual(1.534, s.tMin());
        }
    };
    Spline<2> TestSpline::s(0., 1., { 2,3 }, { 4,5 }, { 6,7 }, { 8,9 });
}