#pragma once
#include "common.h"
#include <utility>

/// Represents a closed Real interval [a, b].
/// a must always be less than or equal to b.
class Interval
{
public:
    Interval();
	Interval(Real a, Real b);
	Real a;
	Real b;
    /// Returns the distance between a and b.
	Real length() const;
    /// Returns true iff t is equal to a or b, or lies between them.
	bool contains(Real t) const;
    /// Returns true iff x is a proper subset of this interval.
	bool contains(const Interval& x) const;
    /// Returns true iff the intervals have nonempty intersection.
    bool intersects(const Interval& x) const;
    /// Returns the midpoint of the interval.
	Real middle() const;
    /// Provides a total order on intervals, comparing by a then b.
	bool operator<(const Interval& x) const;
    /// Returns a pair of intervals [a, middle()], [middle(), b].
    std::pair<Interval, Interval> split() const;
    /// Returns a pair of intervals [a, middle()], [middle(), b].
    std::pair<Interval, Interval> split(Real x) const;
};

