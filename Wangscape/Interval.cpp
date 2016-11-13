#include "Interval.h"
#include <limits>
#include <string>
#include <algorithm>

Interval::Interval() :
    a(-std::numeric_limits<Real>::infinity()),
    b(std::numeric_limits<Real>::infinity())
{

}

Interval::Interval(Real a, Real b):
	a(a), b(b)
{
	if (a > b)
	{
        throw std::range_error(
            "Tried to construct an Interval object with a (" +
            std::to_string(a) +
            ") greater than or equal to b (" +
            std::to_string(b) +
        ")");
	}
}

Real Interval::length() const
{
	return b - a;
}

Real Interval::middle() const
{
	return (a + b) / (Real)2;
}

Real Interval::distance(Real t) const
{
    if (contains(t))
        return 0.;
    return std::min(abs(t - a), abs(t - b));
}

Real Interval::distance(const Interval & x) const
{
    if (intersects(x))
        return 0;
    return std::min(distance(x.a), distance(x.b));
}

bool Interval::contains(Real t) const
{
	return (t >= a && t <= b);
}

bool Interval::contains(const Interval & x) const
{
	return a <= x.a && b >= x.b;
}

bool Interval::intersects(const Interval & x) const
{
    return std::max(a, x.a) <= std::min(b, x.b);
}

bool Interval::operator<(const Interval& x) const
{
	if (a == x.a)
		return b < x.b;
	return a < x.a;
}

std::pair<Interval, Interval> Interval::split() const
{
    return Interval::split(middle());
}

std::pair<Interval, Interval> Interval::split(Real x) const
{
    return std::make_pair(Interval(a, x), Interval(x, b));
}
