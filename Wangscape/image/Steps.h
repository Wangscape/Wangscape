#pragma once

#include <vector>
#include "Vector.h"

const static std::vector<IVec> ORTHOGONAL_STEPS{
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const static std::vector<IVec> ORTHODIAGONAL_STEPS{
    {0, 1}, {1, 0}, {0, -1}, {-1, 0},
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};