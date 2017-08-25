#pragma once
#include <vmmlib/vector.hpp>
#include <SFML/System/Vector2.hpp>
#include <armadillo>

template<typename T>
using Vector = vmml::Vector<2, T>;

typedef Vector<int> IVec;
typedef Vector<unsigned int> UVec;
typedef Vector<double> DVec;

inline IVec makeIVec(sf::Vector2i v)
{
    return IVec(v.x, v.y);
}

inline UVec makeUVec(sf::Vector2u v)
{
    return UVec(v.x, v.y);
}

inline DVec makeDVec(sf::Vector2<double> v)
{
    return DVec(v.x, v.y);
}

inline UVec makeUVec(arma::SizeMat v)
{
    return UVec(v.n_cols, v.n_rows);
}