#include "Interval.h"
#include <limits>
#include <assert.h>
#include <iostream>

Interval::Interval(Real a_, Real b_):
	a(a_), b(b_)
{
	if (a > b)
	{
		std::cerr << "Tried to construct an Interval object with a (" << a << ") greater than or equal to b (" << b << ")";
		exit(1);
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