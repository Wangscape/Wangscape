#include "Interval.h"
#include <limits>
#include <string>

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

bool Interval::contains(Real t) const
{
	return (t >= a && t <= b);
}

bool Interval::contains(const Interval & x) const
{
	return a <= x.a && b >= x.b;
}

bool Interval::operator<(const Interval& x) const
{
	if (a == x.a)
		return b < x.b;
	return a < x.a;
}

std::pair<Interval, Interval> Interval::split() const
{
    return std::make_pair(Interval(a, middle()), Interval(middle(), b));
}
