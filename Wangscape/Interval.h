#pragma once
#include "common.h"

/// Represents a closed Real interval [a, b].
/// a must always be less than or equal to b.
class Interval
{
public:
	Interval(Real a_, Real b_);
	Real a;
	Real b;
    /// Returns the distance between a and b.
	Real length() const;
    /// Returns true iff t is equal to a or b, or lies between them.
	bool contains(Real t) const;
    /// Returns true iff x is a proper subset of this interval.
	bool contains(const Interval& x) const;
    /// Returns the midpoint of the interval.
	Real middle() const;
    /// Provides a total order on intervals, comparing by a then b.
	bool operator<(const Interval& x) const;
};

