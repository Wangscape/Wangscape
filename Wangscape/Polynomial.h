#pragma once
#include <boost/math/tools/polynomial.hpp>
#include "common.h"
class Polynomial : public boost::math::tools::polynomial<Real>
{
public:
    using boost::math::tools::polynomial<Real>::polynomial;
    /// Returns a new polynomial representing the nth derivative, where n=order.
    /// The degree of the polynomial must be greater than or equal to the order of the derivative.
    Polynomial derivative(size_t order = 1) const;

};
// Note that the zero polynomial cannot be evaluated in Boost 1.62.0,
// Due to https://svn.boost.org/trac/boost/ticket/12532

//typedef boost::math::tools::polynomial<Real> Polynomial;