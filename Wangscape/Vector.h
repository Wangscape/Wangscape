#pragma once
#include <vmmlib/vector.hpp>
#include <SFML/System/Vector2.hpp>
#include <armadillo>

template<typename T>
using Vector = vmml::Vector<2, T>;

typedef Vector<int> IVec;
typedef Vector<unsigned int> UVec;
typedef Vector<double> DVec;

template<typename T>
inline Vector<T> makeVector(sf::Vector2<T> v)
{
    return Vector<T>{v.x, v.y};
}

inline UVec makeUVec(arma::SizeMat v)
{
    return UVec(v.n_cols, v.n_rows);
}

inline IVec makeIVec(arma::SizeMat v)
{
    return IVec(makeUVec(v));
}
