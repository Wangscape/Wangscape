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
    Real evaluate(Real t) const;
};

class PolynomialAugmented
{
public:
    typedef std::pair<Real, Real> Extremum;
    typedef std::vector<Extremum> Extrema;

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