#pragma once
#include <cstddef>

/// Numeric type used for all spline calculations
typedef double Real;
/// Polynomial coefficients with magnitude smaller than this
/// are replaced with zero.
static Real const COEFFICIENT_THRESHOLD = 1.e-13;

static size_t const CORNERS = 4;