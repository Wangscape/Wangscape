#pragma once
#include "ModuleGroup.h"
#include "CornerCombinerBase.h"
#include "../Reseedable.h"

namespace noise
{
namespace module
{

Reseedable makeQuadrantSelector(Reseedable& source, bool x_positive, bool y_positive);

// Makes a CornerCombiner scaled and clamped to the interval [-1., 1.].
Reseedable makeCornerCombiner(bool x_positive, bool y_positive, double power = 2.);

// Makes a NormLPQ clamped to the interval [min, 1.].
Reseedable makeEdgeFavouringMask(double p, double q=1., double min=-1.);

// Makes a noise module that rescales a module from range [-1,1] to range [min,max].
Reseedable makeMovingScaleBias(Reseedable& source, Reseedable& min, Reseedable& max);

// Makes a noise module with value equal to x.
Reseedable makeX();

// Makes a noise module with value equal to y.
Reseedable makeY();

// Makes a noise module with value equal to z.
Reseedable makeZ();

// Makes a constant noise module with value c.
Reseedable makeConst(double c);

// Makes a MovingScaleBias instance with ranges:
// [1,1] when d((x,y),origin) == 0,
// [0,0] when d((x,y),origin) >= length,
// [0,1] when d((x,y),origin) == length/2,
// where origin is determined by the *_positive parameters.
// The middle_length parameter controls the size
// of the region with range [0,1].
// It must be less than length.
Reseedable makeLinearMovingScaleBias(Reseedable & source,
                                     bool x_positive, bool y_positive,
                                     double length = 1., double middle_length = 0.);

// Makes a placeholder noise module (a Perlin noise module with typical parameters).
Reseedable makePlaceholder(int seed = 0,
                           int octaves = 5,
                           double frequency = 1.,
                           double lacunarity = 2.,
                           double persistence = 0.5,
                           NoiseQuality quality = NoiseQuality::QUALITY_FAST,
                           double origin_x=1.1,
                           double origin_y=2.2,
                           double origin_z=3.3);

} // namespace module
} // namespace noise
