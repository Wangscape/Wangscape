#pragma once
#include "ModuleGroup.h"
#include "CornerCombinerBase.h"
#include "Reseedable.h"

//ModuleGroup::ModulePtr makeQuadrantSelector(bool x,  bool y)

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

// Makes a MovingScaleBias instance which grows linearly from [0,0] to [0,1], then shrinks to [1,1].
Reseedable makeLinearMovingScaleBias(Reseedable& source, bool x,
                                     double length = 1., double middle_length = 0.);

// Makes a placeholder noise module (a Perlin noise module with typical parameters).
Reseedable makePlaceholder(int seed = 0,
                           int octaves = 5,
                           double frequency = 1.,
                           double lacunarity = 2.,
                           double persistence = 0.5,
                           noise::NoiseQuality quality = noise::QUALITY_FAST,
                           double origin_x=1.1,
                           double origin_y=2.2,
                           double origin_z=3.3);
