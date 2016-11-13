#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../Wangscape/Curve.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WangscapeTest
{
	TEST_CLASS(TestCurve)
	{
	public:
        static Real start;
        static Real end;
        static Vector<2> start_value;
        static Vector<2> end_value;
        static Vector<2> start_deriv;
        static Vector<2> end_deriv;
        static Curve<2> c;
        TEST_METHOD_INITIALIZE(TestCurveSetup)
        {
            start = (Real)-2.396;
            end = (Real)3.947;
            start_value = { (Real)2.45, (Real)8.36 };
            end_value = { (Real)-6.24, (Real)9.10 };
            start_deriv = { (Real)0.47, (Real)-5.28 };
            end_deriv = { (Real)-0.21, (Real)-7.83 };
            c = Curve2(Interval(start, end),
                       { start_value, start_deriv },
                       { end_value, end_deriv });
        }
        TEST_METHOD_CLEANUP(TestCurveTearDown)
        {

        }
        TEST_METHOD(TestCurveValid)
        {
            Assert::IsTrue(c.valid());
        }
        TEST_METHOD(TestCurveLinear)
        {
            Curve<2> axis(Interval(-2, 2),
                          { { -2,0 },{ 1,0 } },
                          { {  2,0 },{ 1,0 } });
            Curve<2>::BoundingBoxN bb = axis.boundingBox();
            Assert::AreEqual(-2., bb[0].a, 0.000001);
            Assert::AreEqual(2., bb[0].b, 0.000001);
            Assert::AreEqual(0., bb[1].a, 0.000001);
            Assert::AreEqual(0., bb[1].b, 0.000001);
        }
        TEST_METHOD(TestCurveGetInterval)
        {
            Assert::AreEqual(start, c.getInterval().a);
            Assert::AreEqual(end, c.getInterval().b);
        }
        TEST_METHOD(TestCurveGetStart)
        {
            Assert::AreEqual(start_value[0], c.getStart().first[0]);
            Assert::AreEqual(start_value[1], c.getStart().first[1]);
            Assert::AreEqual(start_deriv[0], c.getStart().second[0]);
            Assert::AreEqual(start_deriv[1], c.getStart().second[1]);
        }
        TEST_METHOD(TestCurveGetEnd)
        {
            Assert::AreEqual(end_value[0], c.getEnd().first[0]);
            Assert::AreEqual(end_value[1], c.getEnd().first[1]);
            Assert::AreEqual(end_deriv[0], c.getEnd().second[0]);
            Assert::AreEqual(end_deriv[1], c.getEnd().second[1]);
        }
		TEST_METHOD(TestCurveEval)
		{
            Assert::AreEqual(start_value[0], c.evaluate(start)[0]);
            Assert::AreEqual(start_value[1], c.evaluate(start)[1]);
            Assert::AreEqual(end_value[0], c.evaluate(end)[0]);
            Assert::AreEqual(end_value[1], c.evaluate(end)[1]);
		}
        TEST_METHOD(TestCurveDeriv)
        {
            Assert::AreEqual(start_deriv[0], c.derivative(start)[0]);
            Assert::AreEqual(start_deriv[1], c.derivative(start)[1]);
            Assert::AreEqual(end_deriv[0], c.derivative(end)[0]);
            Assert::AreEqual(end_deriv[1], c.derivative(end)[1]);
        }
        TEST_METHOD(TestCurveAlterStart)
        {
            c.alterStart((Real)-10.1, { { (Real)1.1,(Real)2.2 },{ (Real)3.3,(Real)4.4 } });
            Assert::IsTrue(c.valid());

            Assert::AreEqual((Real)-10.1, c.getInterval().a);
            Assert::AreEqual(end, c.getInterval().b);

            Assert::AreEqual((Real)1.1, c.evaluate(-10.1)[0]);
            Assert::AreEqual((Real)2.2, c.evaluate(-10.1)[1]);
            Assert::AreEqual(end_value[0], c.evaluate(end)[0]);
            Assert::AreEqual(end_value[1], c.evaluate(end)[1]);

            Assert::AreEqual((Real)3.3, c.derivative(-10.1)[0]);
            Assert::AreEqual((Real)4.4, c.derivative(-10.1)[1]);
            Assert::AreEqual(end_deriv[0], c.derivative(end)[0]);
            Assert::AreEqual(end_deriv[1], c.derivative(end)[1]);
        }
        TEST_METHOD(TestCurveAlterEnd)
        {
            c.alterEnd((Real)10.1, { { (Real)1.1,(Real)2.2 },{ (Real)3.3,(Real)4.4 } });
            Assert::IsTrue(c.valid());

            Assert::AreEqual(start, c.getInterval().a);
            Assert::AreEqual((Real)10.1, c.getInterval().b);

            Assert::AreEqual(start_value[0], c.evaluate(start)[0]);
            Assert::AreEqual(start_value[1], c.evaluate(start)[1]);
            Assert::AreEqual((Real)1.1, c.evaluate(10.1)[0]);
            Assert::AreEqual((Real)2.2, c.evaluate(10.1)[1]);

            Assert::AreEqual(start_deriv[0], c.derivative(start)[0]);
            Assert::AreEqual(start_deriv[1], c.derivative(start)[1]);
            Assert::AreEqual((Real)3.3, c.derivative(10.1)[0]);
            Assert::AreEqual((Real)4.4, c.derivative(10.1)[1]);
        }
        TEST_METHOD(TestCurveIntermediate)
        {
            c = Curve<2>({ -1., 1. },
                         { {-10.,-5.},{10., 5.} },
                         { {10.,5.},{10.,5.} });

            Assert::AreEqual(-5., c.evaluate(-0.5)[0],0.0000001);
            Assert::AreEqual(0., c.evaluate(0.)[0], 0.0000001);
            Assert::AreEqual(5., c.evaluate(0.5)[0], 0.0000001);

            Assert::AreEqual(-2.5, c.evaluate(-0.5)[1], 0.0000001);
            Assert::AreEqual(0., c.evaluate(0.)[1], 0.0000001);
            Assert::AreEqual(2.5, c.evaluate(0.5)[1], 0.0000001);

            Assert::AreEqual(10., c.derivative(-0.5)[0], 0.0000001);
            Assert::AreEqual(10., c.derivative(0.)[0], 0.0000001);
            Assert::AreEqual(10., c.derivative(0.5)[0], 0.0000001);

            Assert::AreEqual(5., c.derivative(-0.5)[1], 0.0000001);
            Assert::AreEqual(5., c.derivative(0.)[1], 0.0000001);
            Assert::AreEqual(5., c.derivative(0.5)[1], 0.0000001);
        }
        TEST_METHOD(TestCurveRange)
        {
            Curve<2> cubic(Interval(-2, 2),
                           { {-2,-6}, {1,11} },
                           { { 2, 6}, {1,11} });
            Curve<2>::BoundingBoxN bb = cubic.boundingBox();
            Assert::AreEqual(-2., bb[0].a, 0.000001);
            Assert::AreEqual(2., bb[0].b, 0.000001);
            Assert::AreEqual(-6., bb[1].a, 0.000001);
            Assert::AreEqual(6., bb[1].b, 0.000001);
            Assert::IsTrue(boxesIntersect(bb, bb));
        }
        TEST_METHOD(TestCurveIntersection)
        {
            Curve<2> cubic(Interval(-2, 2),
                           { { -2,-6 },{ 1,11 } },
                           { { 2, 6 },{ 1,11 } });
            std::vector<Curve<2>::FramePair> intersections;
            Curve<2> axis(Interval(-2,2),
                          { { -2,0 },{ 1,0 } },
                          { {  2,0 },{ 1,0 } });
            cubic.findIntersections(axis, intersections, 10, 0.001);
            for (auto it : intersections)
            {
                Assert::IsTrue(boxesIntersect(it.first.second, it.second.second), L"Allegedly intersecting frames do not intersect");
                BoundingBox<2> bb1 = cubic.makeRange(it.first.first);
                BoundingBox<2> bb2 = axis.makeRange(it.second.first);
                Assert::AreEqual(bb1[0].a, it.first.second[0].a, L"Left intersection bbox does not match tval interval: lower bound of dimension 0");
                Assert::AreEqual(bb1[0].b, it.first.second[0].b, L"Left intersection bbox does not match tval interval: upper bound of dimension 0");
                Assert::AreEqual(bb2[0].a, it.second.second[0].a, L"Right intersection bbox does not match tval interval: lower bound of dimension 0");
                Assert::AreEqual(bb2[0].b, it.second.second[0].b, L"Right intersection bbox does not match tval interval: upper bound of dimension 0");
                Assert::AreEqual(bb1[1].a, it.first.second[1].a, L"Left intersection bbox does not match tval interval: lower bound of dimension 1");
                Assert::AreEqual(bb1[1].b, it.first.second[1].b, L"Left intersection bbox does not match tval interval: upper bound of dimension 1");
                Assert::AreEqual(bb2[1].a, it.second.second[1].a, L"Right intersection bbox does not match tval interval: lower bound of dimension 1");
                Assert::AreEqual(bb2[1].b, it.second.second[1].b, L"Right intersection bbox does not match tval interval: upper bound of dimension 1");
            }
            Assert::AreEqual((size_t)3, intersections.size(), L"Incorrect number of solutions found");
            std::sort(intersections.begin(),intersections.end() );
            Assert::IsTrue((boxesIntersect<2>(intersections[0].first.second, { Interval(-1.,-1.), Interval(0.,0.) }) ||
                            boxesIntersect<2>(intersections[0].second.second, { Interval(-1.,-1.), Interval(0.,0.) })),
                           L"Neither left nor right intersection bbox contains true first solution");
            Assert::IsTrue((boxesIntersect<2>(intersections[1].first.second, { Interval(0.,0.), Interval(0.,0.) }) ||
                            boxesIntersect<2>(intersections[1].second.second, { Interval(0.,0.), Interval(0.,0.) })),
                           L"Neither left nor right intersection bbox contains true second solution");
            Assert::IsTrue((boxesIntersect<2>(intersections[2].first.second, { Interval(1.,1.), Interval(0.,0.) }) ||
                            boxesIntersect<2>(intersections[2].second.second, { Interval(1.,1.), Interval(0.,0.) })),
                           L"Neither left nor right intersection bbox contains true third solution");

        }
        TEST_METHOD(TestLinearIntersection)
        {
            Curve<2> positive(Interval(-2.2, 2.7),
            { { -2.2,-4.4 },{ 1.,2. } },
            { {  2.7, 5.4 },{ 1.,2. } });
            Curve<2> negative(Interval(-3.4, 2.1),
            { { -3.4, 6.8 },{ 1.,-2. } },
            { { 2.1, -4.2 },{ 1.,-2. } });
            std::vector<Curve<2>::FramePair> intersections;
            positive.findIntersections(negative, intersections, 10, 0.01);
            for (auto it : intersections)
            {
                Assert::IsTrue(boxesIntersect(it.first.second, it.second.second), L"Allegedly intersecting frames do not intersect");
                BoundingBox<2> bb1 = positive.makeRange(it.first.first);
                BoundingBox<2> bb2 = negative.makeRange(it.second.first);
                Assert::AreEqual(bb1[0].a, it.first.second[0].a, L"Left intersection bbox does not match tval interval: lower bound of dimension 0");
                Assert::AreEqual(bb1[0].b, it.first.second[0].b, L"Left intersection bbox does not match tval interval: upper bound of dimension 0");
                Assert::AreEqual(bb2[0].a, it.second.second[0].a, L"Right intersection bbox does not match tval interval: lower bound of dimension 0");
                Assert::AreEqual(bb2[0].b, it.second.second[0].b, L"Right intersection bbox does not match tval interval: upper bound of dimension 0");
                Assert::AreEqual(bb1[1].a, it.first.second[1].a, L"Left intersection bbox does not match tval interval: lower bound of dimension 1");
                Assert::AreEqual(bb1[1].b, it.first.second[1].b, L"Left intersection bbox does not match tval interval: upper bound of dimension 1");
                Assert::AreEqual(bb2[1].a, it.second.second[1].a, L"Right intersection bbox does not match tval interval: lower bound of dimension 1");
                Assert::AreEqual(bb2[1].b, it.second.second[1].b, L"Right intersection bbox does not match tval interval: upper bound of dimension 1");
            }
            Assert::AreEqual((size_t)1, intersections.size(), L"Incorrect number of solutions found");
            Assert::IsTrue((boxesIntersect<2>(intersections[0].first.second, { Interval(0.,0.), Interval(0.,0.) }) ||
                            boxesIntersect<2>(intersections[0].second.second, { Interval(0.,0.), Interval(0.,0.) })),
                            L"Neither left nor right intersection bbox contains true solution");
        }
    private:
	};
    Real TestCurve::start;
    Real TestCurve::end;
    Vector<2> TestCurve::start_value;
    Vector<2> TestCurve::end_value;
    Vector<2> TestCurve::start_deriv;
    Vector<2> TestCurve::end_deriv;
    Curve<2> TestCurve::c(Interval(0, 1),
                          { {1,2}, {3,4 } },
                          { {5,6}, {7,8 } });
}