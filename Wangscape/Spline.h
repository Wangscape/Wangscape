#pragma once
#include <map>
#include <stdexcept>
#include <array>
#include "common.h"
#include "Polynomial.h"
#include "Curve.h"
#include "Interval.h"

/// Describes a continuously differentiable cubic spline S(t) = (x1, ..., xn) in N dimensions.
template<int N> class Spline
{
public:
    typedef std::map<Interval, Curve<N> > Map;
    typedef typename Map::const_iterator MapConstIter;
    /// Initialises the spline with a single curve.
    /// The curve will have S(lower) = start, S(upper) = end, S'(lower) = start_deriv, S'(upper) = end_deriv.
    Spline(Real lower, Real upper,
           Vector<N> start, Vector<N> end,
           Vector<N> start_deriv, Vector<N> end_deriv);

    /// Returns the minimum t value at which the spline can be evaluated.
    Real tMin() const;
    /// Returns the maximum t value at which the spline can be evaluated.
    Real tMax() const;
    
    /// Returns the position of the spline at the given value of t.
    /// t must lie in the closed interval [tMin(), tMax()].
    Vector<N> evaluate(Real t) const;
    /// Returns the nth derivative of the spline at the given value of t.
    /// t must lie in the closed interval [tMin(), tMax()].
    Vector<N> derivative(Real t, size_t order = 1) const;

    /// Alters the value and derivative of the spline at the given value of t.
    void setKnot(Real t, Vector<N> new_value, Vector<N> new_derivative);
    /// Alters the value of the spline at the given value of t.
    /// t must lie in the closed interval [tMin(), tMax()].
    void setKnotValue(Real t, Vector<N> new_value);
    /// Alters the derivative of the spline at the given value of t.
    /// t must lie in the closed interval [tMin(), tMax()].
    void setKnotDerivative(Real t, Vector<N> new_derivative);
    /// Adds a new knot if one is not already present, without significantly affecting the shape of the curve.
    /// t must lie in the closed interval [tMin(), tMax()].
    void setKnotNoChange(Real t);
    /// Removes a knot.
    /// t exactly match the t value of an existing knot.
    /// If t is an endpoint, an end section of the spline is removed.
    /// Otherwise, the two curves incident merge into one, possibly with a different shape.
    void removeKnot(Real t);
    /// Returns true iff:
    /// * Each pair of adjacent intervals intersects at a single point,
    /// * The spline is continuous at all knots,
    /// * The spline is continuously differentiable at all knots.
    bool valid(Real max_relative_error=0.000001) const;
    ///// Returns a constant iterator 
    MapConstIter cbegin() const;
    MapConstIter cend() const;
    //MapConstIter crbegin() const;
    //MapConstIter crend() const;
    void findIntersections(const Curve<N>& c, typename Curve<N>::Intersections& intersections, size_t max, Real tolerance) const;
    void findIntersections(const Spline<N>& s, typename Curve<N>::Intersections& intersections, size_t max, Real tolerance) const;
protected:
    typedef typename Map::iterator MapIter;

    Map mData;

    /// Returns a const iterator pointing to an interval containing t.
    /// When there are two intervals, the first is returned.
    MapConstIter findInterval(Real t) const;
    MapIter findInterval(Real t);
    Vector<N> evaluate(Real t, MapConstIter hint) const;
    Vector<N> derivative(Real t, MapConstIter hint, int order = 1) const;

    void alterKnot(Real t, MapIter hint, Vector<N> new_value, Vector<N> new_derivative);
    void addInternalKnot(Real t, MapIter hint, Vector<N> new_value, Vector<N> new_derivative);

};

typedef Spline<2> Spline2;

template<int N>
inline Spline<N>::Spline(Real lower, Real upper,
                         Vector<N> start, Vector<N> end,
                         Vector<N> start_deriv, Vector<N> end_deriv)
{
    mData.insert(std::make_pair(Interval(lower, upper), Curve<2>(Interval(lower, upper),
                                             { start, start_deriv },
                                             { end, end_deriv })));
}

template<int N>
inline Real Spline<N>::tMin() const
{
    return (*(mData.cbegin())).first.a;
}

template<int N>
inline Real Spline<N>::tMax() const
{
    return (*(--(mData.cend()))).first.b;
}

template<int N>
inline typename Vector<N> Spline<N>::evaluate(Real t) const
{
    MapConstIter hint = findInterval(t);
    return evaluate(t, hint);
}

template<int N>
inline typename Vector<N> Spline<N>::evaluate(Real t, MapConstIter hint) const
{
    if ((*hint).first.contains(t))
        return (*hint).second.evaluate(t);
    else if (t < tMin())
        throw std::runtime_error("Spline<N>::evaluate(t, hint) called with t less than Spline<N>::tMin()");
        //std::cerr << "Spline<N>::evaluate(t, hint) called with t (" << t << ") less than Spline<N>::tMin() (" << tMin() << ")";
    else if (t > tMax())
        throw std::runtime_error("Spline<N>::evaluate(t, hint) called with t greater than Spline<N>::tMax()");
        //std::cerr << "Spline<N>::evaluate(t, hint) called with t (" << t << ") greater than Spline<N>::tMax() (" << tMax() << ")";
    else
        throw std::runtime_error("Incorrect hint passed to Spline<N>::evaluate(t, hint)");
        //std::cerr << "Incorrect hint with interval [" << (*hint).first.a << "," << (*hint).first.b << "] passed to Spline<N>::evaluate(t, hint) (t = " << t << ")";
    //exit(1);
}

template<int N>
inline typename Vector<N> Spline<N>::derivative(Real t, size_t order) const
{
    MapConstIter hint = findInterval(t);
    return derivative(t, hint, order);
}

template<int N>
inline typename Vector<N> Spline<N>::derivative(Real t, MapConstIter hint, int order) const
{
    if ((*hint).first.contains(t))
        return (*hint).second.derivative(t, order);
    else if (t < tMin())
        throw std::runtime_error("Spline<N>::derivative(t, hint) called with t less than Spline<N>::tMin()");
        //std::cerr << "Spline<N>::derivative(t, hint) called with t (" << t << ") less than Spline<N>::tMin() (" << tMin() << ")";
    else if (t > tMax())
        throw std::runtime_error("Spline<N>::derivative(t, hint) called with t greater than Spline<N>::tMax()");
        //std::cerr << "Spline<N>::derivative(t, hint) called with t (" << t << ") greater than Spline<N>::tMax() (" << tMax() << ")";
    else
        throw std::runtime_error("Incorrect hint passed to Spline<N>::derivative(t, hint)");
        //std::cerr << "Incorrect hint with interval [" << (*hint).first.a << "," << (*hint).first.b << "] passed to Spline<N>::derivative(t, hint) (t = " << t << ")";
    //exit(1);
}

template<int N>
inline void Spline<N>::setKnot(Real t, Vector<N> new_value, Vector<N> new_derivative)
{
    Real t_min = tMin();
    if (t < t_min)
    {
        mData.insert(std::make_pair(Interval(t, t_min),
                     Curve<2>(Interval(t, t_min),
                              { new_value, new_derivative },
                              { evaluate(t_min), derivative(t_min) })));
        return;
    }
    Real t_max = tMax();
    if (t > t_max)
    {
        mData.insert(std::make_pair(Interval(t_max, t),
                        Curve<2>(Interval(t_max, t),
                                 { evaluate(t_max), derivative(t_max) },
                                 { new_value, new_derivative })));
        return;
    }
    MapIter hint = findInterval(t);
    if (t == (*hint).first.a)
        alterKnot(t, hint, new_value, new_derivative);
    else if (t == (*hint).first.b)
        alterKnot(t, hint, new_value, new_derivative);
    else
        addInternalKnot(t, hint, new_value, new_derivative);
}

template<int N>
inline void Spline<N>::setKnotValue(Real t, Vector<N> new_value)
{
    Vector<N> existing_derivative = derivative(t);
    setKnot(t, new_value, existing_derivative);
}

template<int N>
inline void Spline<N>::setKnotDerivative(Real t, Vector<N> new_derivative)
{
    Vector<N> existing_value = evaluate(t);
    setKnot(t, existing_value, new_derivative);
}

template<int N>
inline void Spline<N>::setKnotNoChange(Real t)
{
    Vector<N> existing_value = evaluate(t);
    Vector<N> existing_derivative = derivative(t);
    setKnot(t, existing_value, existing_derivative);
}

template<int N>
inline void Spline<N>::removeKnot(Real t)
{
    if (mData.size() < 2)
    {
        std::cerr << "Tried to remove a knot from a spline with only " << mData.size() << " component curves";
    }
    MapIter it = findInterval(t);
    bool go_left = true;
    if (t == (*it).first.a)
    {
        if (it == mData.begin())
        {
            mData.erase(it);
            return;
        }
    }
    else if (t == (*it).first.b)
    {
        if (it == (--mData.end()))
        {
            mData.erase(it);
            return;
        }
        go_left = false;
    }
    else
    {
        throw std::runtime_error("Tried to remove knot using hint interval that doesn't contain it");
        //std::cerr << "Tried to remove knot at t = " << t << " using hint interval [" << (*it).first.a << "," << (*it).first.b << "]";
        //exit(1);
    }
    MapIter jt = it;
    if (go_left)
        --it;
    else
        ++jt;
    Real a = (*it).first.a;
    Real b = (*jt).first.b;
    Real x = (*it).first.b;
    Curve<N>::KnotValueDerivative start = (*it).second.getStart();
    Curve<N>::KnotValueDerivative end = (*it).second.getEnd();
    mData.erase(Interval(a, x));
    mData.erase(Interval(x, b));
    mData.insert(std::make_pair(Interval(a, b), Curve<N>(Interval(a, b), start, end)));
}

template<int N>
inline bool Spline<N>::valid(Real max_relative_error) const
{
    MapConstIter it = mData.cbegin();
    if (!(*it).second.valid())
        return false;
    MapConstIter jt = it;
    ++jt;
    while (jt != mData.cend())
    {
        Real t = (*it).first.b;
        if (t != (*jt).first.a)
            return false;
        if (!(*jt).second.valid())
            return false;
        if ((*it).second.getEnd().first != (*jt).second.getStart().first)
            return false;
        if ((*it).second.getEnd().second != (*jt).second.getStart().second)
            return false;
        it = jt;
        ++jt;
    }
    return true;
}

template<int N>
inline typename Spline<N>::MapConstIter Spline<N>::cbegin() const
{
    return mData.cbegin();
}

template<int N>
inline typename Spline<N>::MapConstIter Spline<N>::cend() const
{
    return mData.cend();
}

template<int N>
inline void Spline<N>::findIntersections(const Curve<N>& c, typename Curve<N>::Intersections & intersections, size_t max, Real tolerance) const
{
    for (auto it : mData)
    {
        it.second.findIntersections(c, intersections, max, tolerance);
    }
}

template<int N>
inline void Spline<N>::findIntersections(const Spline<N>& s, typename Curve<N>::Intersections & intersections, size_t max, Real tolerance) const
{
    for (auto it = s.cbegin(); it != s.cend(); ++it)
    {
        findIntersections((*it).second, intersections, max, tolerance);
    }
}

template<int N>
inline typename Spline<N>::MapConstIter Spline<N>::findInterval(Real t) const
{
    if (t == tMin())
        return mData.cbegin();
    return --(mData.upper_bound(Interval(t, t)));
}

template<int N>
inline typename Spline<N>::MapIter Spline<N>::findInterval(Real t)
{
    if (t == tMin())
        return mData.begin();
    return --(mData.upper_bound(Interval(t, t)));
}

template<int N>
inline void Spline<N>::alterKnot(Real t, MapIter hint, Vector<N> new_value, Vector<N> new_derivative)
{
    if (t == (*hint).first.a)
    {
        (*hint).second.alterStart(t, { new_value, new_derivative });
        if (hint != mData.begin())
        {
            --hint;
            (*hint).second.alterEnd(t, { new_value, new_derivative });
        }
    }
    else if (t == (*hint).first.b)
    {
        (*hint).second.alterEnd(t, { new_value, new_derivative });
        ++hint;
        if (hint != mData.end())
            (*hint).second.alterStart(t, { new_value, new_derivative });
    }
    else
    {
        throw std::runtime_error("Tried to alter a knot using an incorrect hint");
        //std::cerr << "Tried to alter a knot with t = " << t << " using an incorrect hint with interval [" << (*hint).first.a << "," << (*hint).first.b << "]";
        //exit(1);
    }
}

template<int N>
inline void Spline<N>::addInternalKnot(Real t, MapIter hint, Vector<N> new_value, Vector<N> new_derivative)
{
    Real a = (*hint).first.a;
    Real b = (*hint).first.b;
    if (t == a || t == b)
    {
        throw std::runtime_error("Tried to add a new internal knot, but t is equal to one of the extremes of the interval");
        //std::cerr << "Tried to add a new internal knot with t = " << t << ", but t is equal to one of the extremes of the interval [" << (*hint).first.a << "," << (*hint).first.b << "]";
        //exit(1);
    }
    if (!(*hint).first.contains(t))
    {
        throw std::runtime_error("Tried to add a new internal knot, but t not contained in the hint interval");
        //std::cerr << "Tried to add a new internal knot with t = " << t << ", but t is not contained in the hint interval [" << (*hint).first.a << "," << (*hint).first.b << "]";
        //exit(1);
    }

    Curve<N>::KnotValueDerivative start = (*hint).second.getStart();
    Curve<N>::KnotValueDerivative end = (*hint).second.getEnd();
    mData.erase(hint);
    Interval I(a, t);
    Interval J(t, b);
    mData.insert(std::make_pair(I, Curve<N>(I, start, { new_value, new_derivative })));
    mData.insert(std::make_pair(J, Curve<N>(J, { new_value, new_derivative }, end)));

}
