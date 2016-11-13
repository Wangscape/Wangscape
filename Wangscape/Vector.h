#pragma once

#include <array>

template<int N>
using Vector = std::array<Real, N>;

typedef Vector<2> Vector2;

template<int N>
bool withinErrorBounds(const Vector<N>& expected, const Vector<N>& actual, Real max_relative_error=0.000001)
{
    for (int i = 0; i < N; i++)
    {
        if (expected[i] == (Real)0.0)
        {
            if (expected[i] != actual[i])
                return false;
            continue;
        }
        Real abs_error = abs(expected[i] - actual[i]);
        Real rel_error = abs(abs_error / expected[i]);
        if (rel_error > max_relative_error)
            return false;
    }
    return true;
}
template<int N>
bool almostEqual(const Vector<N>& x, const Vector<N>& y, Real max_relative_error = 0.000001)
{
    for (int i = 0; i < N; i++)
    {
        Real abs_error = abs(x[i] - y[i]);
        Real divisor = (abs(x[i]) + abs(y[i])+(Real)1.)/(Real)2.0;
        Real rel_error = abs_error / divisor;
        if (rel_error > max_relative_error)
            return false;
    }
    return true;
}