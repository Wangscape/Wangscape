#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../Wangscape/Interval.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WangscapeTest
{
    TEST_CLASS(TestInterval)
    {
    public:
        TEST_METHOD(TestIntervalAB)
        {
            Interval I(-1., 1.);
            Assert::AreEqual(-1., I.a);
            Assert::AreEqual(1., I.b);
            I = Interval(4.7, 4.8);
            Assert::AreEqual(4.7, I.a);
            Assert::AreEqual(4.8, I.b);
        }
        TEST_METHOD(TestIntervalLength)
        {
            Assert::AreEqual(2., Interval(-1., 1.).length(), 0.000001);
            Assert::AreEqual(0.1, Interval(4.7, 4.8).length(), 0.000001);
        }
        TEST_METHOD(TestIntervalContains)
        {
            Assert::IsTrue(Interval(-1., 1.).contains(0.));
            Assert::IsTrue(Interval(-1., 1.).contains(-1.));
            Assert::IsTrue(Interval(-1., 1.).contains(1.));
        }
        TEST_METHOD(TestIntervalIntersects)
        {
            Assert::IsTrue(Interval(-1., 1.).intersects(Interval(0., 0.)));
            Assert::IsTrue(Interval(0., 0.).intersects(Interval(-1., 1.)));
            Assert::IsTrue(Interval(-1., 1.).intersects(Interval(0.,2.)));
            Assert::IsTrue(Interval(-1., 1.).intersects(Interval(-2., 0.)));
            Assert::IsTrue(Interval(-1., 1.).intersects(Interval(1., 2.)));
            Assert::IsTrue(Interval(-1., 1.).intersects(Interval(-2., -1.)));
            Assert::IsFalse(Interval(-1., 1.).intersects(Interval(-4., -3.)));
            Assert::IsFalse(Interval(-1., 1.).intersects(Interval(3., 4.)));
        }
        TEST_METHOD(TestIntervalMiddle)
        {
            Assert::AreEqual(0.,Interval(-1., 1.).middle(),0.000001);
            Assert::AreEqual(4.75, Interval(4.7, 4.8).middle(), 0.000001);
        }
        TEST_METHOD(TestIntervalOrder)
        {
            Assert::IsTrue(Interval(0., 0.) < Interval(0., 1.));
            Assert::IsFalse(Interval(0., 0.) < Interval(0., 0.));
            Assert::IsFalse(Interval(0., 3.) < Interval(0., 2.));
            Assert::IsTrue(Interval(0., 2.) < Interval(1., 2.));
            Assert::IsTrue(Interval(0., 3.) < Interval(1., 2.));
        }
        TEST_METHOD(TestIntervalSplit)
        {
            Assert::AreEqual(-1., Interval(-1., 1.).split().first.a);
            Assert::AreEqual(0., Interval(-1., 1.).split().first.b, 0.000001);
            Assert::AreEqual(0., Interval(-1., 1.).split().second.a, 0.000001);
            Assert::AreEqual(1., Interval(-1., 1.).split().second.b);
            Assert::AreEqual(-1., Interval(-1., 1.).split(0.5).first.a);
            Assert::AreEqual(0.5, Interval(-1., 1.).split(0.5).first.b, 0.000001);
            Assert::AreEqual(0.5, Interval(-1., 1.).split(0.5).second.a, 0.000001);
            Assert::AreEqual(1., Interval(-1., 1.).split(0.5).second.b);
        }
        TEST_METHOD(TestBoundingBox)
        {
            BoundingBox<2> bb0({ Interval{ 0,0 }, Interval{ 0,0 } });
            BoundingBox<2> bb1({ Interval{ 0,1 }, Interval{ 0,1 } });
            BoundingBox<2> bb2({ Interval{ 1,2 }, Interval{ 1,2 } });
            Assert::IsTrue(boxesIntersect<2>(bb0, bb0));
            Assert::IsTrue(boxesIntersect<2>(bb1, bb1));
            Assert::IsTrue(boxesIntersect<2>(bb2, bb2));
            Assert::IsTrue(boxesIntersect<2>(bb0,bb1));
            Assert::IsTrue(boxesIntersect<2>(bb1, bb2));
            Assert::IsFalse(boxesIntersect<2>(bb0, bb2));
        }
    };
}