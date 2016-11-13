#pragma once
#include <Eigen/Dense>
#include <array>
#include <iostream>
#include <deque>
#include <utility>
#include "common.h"
#include "Interval.h"
#include "Polynomial.h"
#include "Vector.h"

/// Describes a cubic curve in N dimensions defined on a closed interval.
template<int N>
class Curve
{
public:
    typedef std::pair<Vector<N>, Vector<N>> KnotValueDerivative;
    typedef BoundingBox<N> BoundingBoxN;
    typedef std::pair<Interval, BoundingBoxN> Frame;
    typedef std::pair<Frame, Frame> FramePair;
    typedef std::vector<FramePair> Intersections;
    /// Constructs a new curve defined on the interval I , starting and ending with the given values and derivatives.
    /// I must have nonzero length.
    Curve(Interval I, const KnotValueDerivative& start, const KnotValueDerivative& end);
    /// Returns the closed interval on which the curve is defined.
    const Interval& getInterval() const;
    /// Returns the exact value and derivative of the curve at the start of its interval.
    const KnotValueDerivative& getStart() const;
    /// Returns the exact value and derivative of the curve at the end of its interval.
    const KnotValueDerivative& getEnd() const;
    /// Returns the value of the curve at the given time.
    Vector<N> evaluate(Real t) const;
    /// Returns the derivative of the curve at the given time.
    Vector<N> derivative(Real t, size_t order = 1) const;

    const PolynomialAugmented& polynomial(int i) const;
    const Interval& interval() const;
    void alterStart(Real new_start_t, const KnotValueDerivative& new_start);
    void alterEnd(Real new_end_t, const KnotValueDerivative& new_end);
    bool valid(Real max_relative_error = 0.000001) const;
    void findIntersections(const Curve& c, Intersections& intersections, size_t max, Real tolerance) const;
    const BoundingBoxN& boundingBox() const;
    BoundingBoxN makeRange(const Interval& I) const;
private:
    static int const MATRIX_SIZE = 4;
    typedef Eigen::Matrix<Real, MATRIX_SIZE, MATRIX_SIZE> PolynomialMatrix;
    //typedef Eigen::Matrix<Real, 1, MATRIX_SIZE> PolynomialRow;
    typedef Eigen::Matrix<Real, MATRIX_SIZE, 1> PolynomialColumn;
    Interval mI;
    KnotValueDerivative mStart;
    KnotValueDerivative mEnd;
    std::array<PolynomialAugmented, N> mPolynomials;
    BoundingBoxN mBoundingBox;

    Vector<N> evaluateInexact(Real t) const;
    Vector<N> derivativeInexact(Real t, size_t order = 1) const;
    static PolynomialMatrix constructMatrix(Real lower, Real upper);
    static Polynomial findPoly(Real lower, Real upper,
                               Real start, Real start_deriv,
                               Real end, Real end_deriv);
    void update();
};

typedef Curve<2> Curve2;

template<int N>
Curve<N>::Curve(Interval I, const KnotValueDerivative& start, const KnotValueDerivative& end) :
    mI(I), mStart(start), mEnd(end)
{
    update();
}

template<int N>
inline const Interval & Curve<N>::getInterval() const
{
    return mI;
}

template<int N>
inline const typename Curve<N>::KnotValueDerivative & Curve<N>::getStart() const
{
    return mStart;
}

template<int N>
inline const typename Curve<N>::KnotValueDerivative & Curve<N>::getEnd() const
{
    return mEnd;
}

template<int N>
Vector<N> Curve<N>::evaluate(Real t) const
{
    if (t == mI.a)
        return mStart.first;
    else if (t == mI.b)
        return mEnd.first;
    return evaluateInexact(t);
}

template<int N>
Vector<N> Curve<N>::derivative(Real t, size_t order) const
{
    if (t == mI.a)
        return mStart.second;
    else if (t == mI.b)
        return mEnd.second;
    return derivativeInexact(t, order);
}

template<int N>
inline const PolynomialAugmented & Curve<N>::polynomial(int i) const
{
    return mPolynomials[i];
}

template<int N>
inline const Interval & Curve<N>::interval() const
{
    return mI;
}

template<int N>
inline void Curve<N>::alterStart(Real new_start_t, const KnotValueDerivative & new_start)
{
    mI = Interval(new_start_t, mI.b);
    mStart = new_start;
    update();
}

template<int N>
inline void Curve<N>::alterEnd(Real new_end_t, const KnotValueDerivative & new_end)
{
    mI = Interval(mI.a, new_end_t);
    mEnd = new_end;
    update();
}

template<int N>
inline bool Curve<N>::valid(Real max_relative_error) const
{
    if (!almostEqual(mStart.first, evaluateInexact(mI.a), max_relative_error))
    {
        std::cerr << "start value incorrect";
        return false;
    }
    if (!almostEqual(mEnd.first, evaluateInexact(mI.b), max_relative_error))
    {
        std::cerr << "end value incorrect";
        return false;
    }
    if (!almostEqual(mStart.second, derivativeInexact(mI.a), max_relative_error))
    {
        std::cerr << "start derivative incorrect";
        return false;
    }
    if (!almostEqual(mEnd.second, derivativeInexact(mI.b), max_relative_error))
    {
        std::cerr << "end derivative incorrect";
        return false;
    }
    return true;
}

template<int N>
inline void Curve<N>::findIntersections(const Curve & c,
                                        Intersections& intersections,
                                        size_t max,
                                        Real tolerance) const
{
    if (max < 0)
        return;
    if (!boxesIntersect(mBoundingBox, c.boundingBox()))
        return;
    std::deque<FramePair> dq;
    dq.push_back({ {interval(),makeRange(interval())},
                   {c.interval(), c.makeRange(c.interval())}});
    while (intersections.size() <= max && dq.size() > 0)
    {
        FramePair Fs = dq.front();
        bool stopPath = false;
        while (!stopPath)
        {
            std::pair<Interval, Interval> split1 = Fs.first.first.split();
            std::pair<Interval, Interval> split2 = Fs.second.first.split();
            BoundingBoxN BB1a = makeRange(split1.first);
            BoundingBoxN BB1b = makeRange(split1.second);
            BoundingBoxN BB2a = c.makeRange(split2.first);
            BoundingBoxN BB2b = c.makeRange(split2.second);
            bool possibleIntersectionFound = false;
            stopPath = false;
            auto processBoxes = [&](const BoundingBoxN& BB1, const BoundingBoxN& BB2,
                                    const Interval& I1, const Interval& I2)
            {
                if (boxesIntersect(BB1, BB2))
                {
                    if(!hasDimensionGreaterEqual(BB1, tolerance) &&
                       !hasDimensionGreaterEqual(BB2, tolerance))
                    {
                        // intersection found.
                        bool alreadyFound = false;
                        for (const auto it : intersections)
                        {
                            if ((distanceMax(BB1, it.first.second) <= tolerance) &&
                                (distanceMax(BB2, it.second.second) <= tolerance))
                            {
                                alreadyFound = true;
                                break;
                            }
                        }
                        if (!alreadyFound)
                        {
                            intersections.push_back({ { I1, BB1 },{ I2, BB2 } });
                        }
                        stopPath = true;
                        return;
                    }
                    if (possibleIntersectionFound)
                        dq.push_back({ {I1, BB1}, {I2, BB2} });
                    else
                    {
                        Fs = { {I1,BB1},{I2,BB2} };
                        possibleIntersectionFound = true;
                    }
                }
            };
            processBoxes(BB1a, BB2a,
                         split1.first, split2.first);
            processBoxes(BB1a, BB2b,
                         split1.first, split2.second);
            processBoxes(BB1b, BB2a,
                         split1.second, split2.first);
            processBoxes(BB1b, BB2b,
                         split1.second, split2.second);
            if (!possibleIntersectionFound)
                stopPath = true;
        }
        dq.pop_front();
    }
    return;
}

template<int N>
inline const typename Curve<N>::BoundingBoxN & Curve<N>::boundingBox() const
{
    return mBoundingBox;
}

template<int N>
inline typename Curve<N>::BoundingBoxN Curve<N>::makeRange(const Interval & I) const
{
    BoundingBoxN bb;
    for (int i = 0; i < N; i++)
    {
        bb[i] = mPolynomials[i].makeRange(I);
    }
    return bb;
}

template<int N>
inline void Curve<N>::update()
{
    for (int i = 0; i < N; i++)
    {
        mPolynomials[i] = findPoly(mI.a, mI.b,
                                   mStart.first[i], mStart.second[i],
                                   mEnd.first[i], mEnd.second[i]);
    }
    mBoundingBox = makeRange(mI);
}

template<int N>
inline Polynomial Curve<N>::findPoly(Real lower, Real upper,
                                     Real start, Real start_deriv,
                                     Real end, Real end_deriv)
{
    Curve<N>::PolynomialMatrix mat = constructMatrix(lower, upper);
    Curve<N>::PolynomialColumn v;
    v << start, end, start_deriv, end_deriv;
    Curve<N>::PolynomialColumn solution = mat.colPivHouseholderQr().solve(v);
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        if (abs(solution[i]) < COEFFICIENT_THRESHOLD)
            solution[i] = 0.;

    }
    return Polynomial(solution.data(), MATRIX_SIZE - 1);
}

template<int N>
inline Vector<N> Curve<N>::evaluateInexact(Real t) const
{
    Vector<N> r;
    for (int i = 0; i < N; i++)
    {
        r[i] = mPolynomials[i].polynomial().evaluate(t);
    }
    return r;
}

template<int N>
inline Vector<N> Curve<N>::derivativeInexact(Real t, size_t order) const
{
    Vector<N> r;
    for (int i = 0; i < N; i++)
    {
        r[i] = mPolynomials[i].derivative().evaluate(t);
    }
    return r;
}

template<int N>
inline typename Curve<N>::PolynomialMatrix Curve<N>::constructMatrix(Real lower, Real upper)
{
    //1, L, L^2, L^3
    //1, U, U^2, U^3
    //0, 1, 2*L, 3*L^2
    //0, 1, 2*U, 3*U^2
    Curve<N>::PolynomialMatrix mat;
    Real a = 1;
    Real b = 1;
    mat(2, 0) = 0;
    mat(3, 0) = 0;
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        mat(0, i) = a;
        mat(1, i) = b;
        if (i < MATRIX_SIZE - 1)
        {
            mat(2, i + 1) = a*(i + 1);
            mat(3, i + 1) = b*(i + 1);
        }
        a *= lower;
        b *= upper;
    }
    return mat;
}