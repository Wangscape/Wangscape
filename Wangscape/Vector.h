#pragma once
#include <vmmlib/vector.hpp>

template<typename T>
using Vector = vmml::Vector<2, T>;

typedef Vector<int> IVec;
typedef Vector<unsigned int> UVec;
typedef Vector<double> DVec;
