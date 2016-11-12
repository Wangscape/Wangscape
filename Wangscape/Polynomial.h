#pragma once
#include <boost/math/tools/polynomial.hpp>
#include "common.h"
#include "Interval.h"
typedef boost::math::tools::polynomial<Real> PolynomialBase;

class Polynomial : public PolynomialBase
{
public:
    typedef std::vector<Real> Solutions;
    using PolynomialBase::polynomial;
    Polynomial makeDerivative(size_t order = 1) const;
    Solutions makeSolutions() const;
};

class PolynomialAugmented
{
public:
    typedef std::pair<Real, Real> Extremum;
    typedef std::vector<Extremum> Extrema;
    // 
    PolynomialAugmented() = default;
    PolynomialAugmented(const Polynomial& p);
    const Polynomial& polynomial() const;
    const Polynomial& derivative() const;
    const Extrema& extrema() const;

    Interval makeRange(const Interval& domain) const;
    Interval makeRange(const Interval& domain, const Extrema& restricted_extrema) const;
private:
    Extrema makeExtrema() const;
    Polynomial mPolynomial;
    Polynomial mDerivative;
    Extrema mExtrema;

};


//
//class Polynomial : public PolynomialBase
//{
//public:
//    typedef std::vector<Real> Solutions;
//
//    using PolynomialBase::polynomial;
//    /// Returns a new polynomial representing the nth derivative, where n=order.
//    /// The degree of the polynomial must be greater than or equal to the order of the derivative.
//    Polynomial makeDerivative(size_t order = 1) const;
//    Solutions makeSolutions() const;
//
//};
//// Note that the zero polynomial cannot be evaluated in Boost 1.62.0,
//// Due to https://svn.boost.org/trac/boost/ticket/12532
//
//class PolynomialWithDerivative : public Polynomial
//{
//public:
//    const Polynomial& derivative() const;
//private:
//    Polynomial mDerivative;
//};
//
//class PolynomialWithStationaryPoints : public PolynomialWithDerivative
//{
//public:
//    typedef std::pair<Real, Real> StationaryPoint;
//    typedef std::vector<StationaryPoint> StationaryPointVector;
//    const StationaryPointVector& stationaryPoints() const;
//    bool stationaryEverywhere() const;
//    Interval range(const Interval& domain);
//private:
//    StationaryPointVector mStationaryPoints;
//    bool mStationaryEverywhere;
//};