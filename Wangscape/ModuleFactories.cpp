#include "ModuleFactories.h"
#include "Gradient.h"
#include "NormLPQ.h"
#include "MakeReseedable.h"

using noise::module::Abs;
using noise::module::ScaleBias;
using noise::module::Clamp;
using noise::module::TranslatePoint;
using noise::module::ScalePoint;
using noise::module::Perlin;

Reseedable makePeak(bool x)
{
    Reseedable gradient;
    if (x)
        gradient = makeReseedable(std::make_shared<GradientX>());
    else
        gradient = makeReseedable(std::make_shared<GradientY>());

    std::shared_ptr<Abs> abs = std::make_shared<Abs>();
    abs->SetSourceModule(0, *gradient.module);

    std::shared_ptr<ScaleBias> scale_bias = std::make_shared<ScaleBias>();
    scale_bias->SetSourceModule(0, *abs.get());
    scale_bias->SetScale(-1.);
    scale_bias->SetBias(1.);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert( mg->output_id, makeReseedable(scale_bias) );
    mg->insert( "abs",makeReseedable(abs) );
    mg->insert( "gradient",gradient );

    return makeReseedable(mg);
}

Reseedable makeCornerCombiner(bool x_positive, bool y_positive, double power)
{
    std::shared_ptr<CornerCombinerBase> corner_combiner_base = std::make_shared<CornerCombinerBase>(power);

    std::shared_ptr<ScaleBias> scale_bias = std::make_shared<ScaleBias>();
    scale_bias->SetBias(0.5);
    scale_bias->SetScale(0.5);
    scale_bias->SetSourceModule(0, *corner_combiner_base.get());

    std::shared_ptr<Clamp> clamp = std::make_shared<Clamp>();
    clamp->SetBounds(0., 1.);
    clamp->SetSourceModule(0, *scale_bias.get());

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert( mg->output_id,makeReseedable(clamp) );
    mg->insert( "scale_bias", makeReseedable(scale_bias) );
    mg->insert( "corner_combiner_base", makeReseedable(corner_combiner_base) );

    return makeReseedable(mg);

}

Reseedable makeEdgeFavouringMask(double p, double q, double min)
{
    std::shared_ptr<NormLPQ> norm_lp_q = std::make_shared<NormLPQ>(p, q);

    std::shared_ptr<TranslatePoint> translate = std::make_shared<TranslatePoint>();
    translate->SetXTranslation(-1.);
    translate->SetYTranslation(-1.);
    translate->SetZTranslation(0.);
    translate->SetSourceModule(0, *norm_lp_q.get());

    std::shared_ptr<ScalePoint> scale_point = std::make_shared<ScalePoint>();
    scale_point->SetXScale(2.);
    scale_point->SetYScale(2.);
    scale_point->SetZScale(0.);
    scale_point->SetSourceModule(0, *translate.get());

    std::shared_ptr<ScaleBias> scale_bias = std::make_shared<ScaleBias>();
    scale_bias->SetBias(min);
    scale_bias->SetScale(1. - min);
    scale_bias->SetSourceModule(0, *scale_point.get());

    std::shared_ptr<Clamp> clamp = std::make_shared<Clamp>();
    clamp->SetBounds(min, 1.);
    clamp->SetSourceModule(0, *scale_bias.get());

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert( mg->output_id, makeReseedable(clamp) );
    mg->insert( "scale_bias",makeReseedable(scale_bias) );
    mg->insert( "scale_point",makeReseedable(scale_point) );
    mg->insert( "translate", makeReseedable(translate) );
    mg->insert( "norm_lp_q", makeReseedable(norm_lp_q) );

    return makeReseedable(mg);
}

Reseedable makePlaceholder(int seed,
                           int octaves,
                           double frequency,
                           double lacunarity,
                           double persistence,
                           noise::NoiseQuality quality)
{
    std::shared_ptr<Perlin> placeholder = std::make_shared<Perlin>();
    placeholder->SetSeed(seed);
    placeholder->SetOctaveCount(octaves);
    placeholder->SetFrequency(frequency);
    placeholder->SetLacunarity(lacunarity);
    placeholder->SetPersistence(persistence);
    placeholder->SetNoiseQuality(quality);
    return makeReseedable(placeholder);
}
