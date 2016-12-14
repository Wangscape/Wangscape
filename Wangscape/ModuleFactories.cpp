#include "ModuleFactories.h"
#include "Gradient.h"
#include "NormLPQ.h"

Reseedable makePeak(bool x)
{
    ModulePtr gradient;
    if (x)
        gradient = std::make_shared<GradientX>();
    else
        gradient = std::make_shared<GradientY>();

    ModulePtr abs = std::make_shared<noise::module::Abs>();
    abs.get()->SetSourceModule(0, *gradient.get());

    ModulePtr scale_bias = std::make_shared<noise::module::ScaleBias>();
    scale_bias.get()->SetSourceModule(0, *abs.get());
    ((std::shared_ptr<noise::module::ScaleBias>&)*scale_bias.get())->SetScale(-1.);
    ((std::shared_ptr<noise::module::ScaleBias>&)*scale_bias.get())->SetBias(1.);

    ModulePtr mg(new ModuleGroup);
    ModuleGroup& mg_r = (ModuleGroup&)*mg.get();
    mg_r.modules.insert({ mg_r.output_id, makeReseedable(scale_bias) });
    mg_r.modules.insert({ "abs",makeReseedable(abs) });
    mg_r.modules.insert({ "gradient",makeReseedable(gradient) });

    return makeReseedable(mg);
}

Reseedable makeCornerCombiner(bool x_positive, bool y_positive, double power)
{
    ModulePtr corner_combiner_base = std::make_shared<CornerCombinerBase>(power);

    ModulePtr scale_bias = std::make_shared<noise::module::ScaleBias>();
    ((noise::module::ScaleBias&)*scale_bias.get()).SetBias(0.5);
    ((noise::module::ScaleBias&)*scale_bias.get()).SetScale(0.5);
    scale_bias.get()->SetSourceModule(0, *corner_combiner_base.get());

    ModulePtr clamp = std::make_shared<noise::module::Clamp>();
    ((noise::module::Clamp&)*clamp.get()).SetBounds(0., 1.);
    clamp.get()->SetSourceModule(0, *scale_bias.get());

    ModulePtr mg = std::make_shared<ModuleGroup>();
    ModuleGroup& mg_r = (ModuleGroup&)*mg.get();
    mg_r.modules.insert({ mg_r.output_id,makeReseedable(clamp) });
    mg_r.modules.insert({ "scale_bias", makeReseedable(scale_bias) });
    mg_r.modules.insert({ "corner_combiner_base", makeReseedable(corner_combiner_base) });

    return makeReseedable(mg);

}

Reseedable makeEdgeFavouringMask(double p, double q, double min)
{
    ModulePtr norm_lp_q = std::make_shared<NormLPQ>(p, q);

    ModulePtr translate = std::make_shared<noise::module::TranslatePoint>();
    ((noise::module::TranslatePoint&)*translate.get()).SetXTranslation(-1.);
    ((noise::module::TranslatePoint&)*translate.get()).SetYTranslation(-1.);
    ((noise::module::TranslatePoint&)*translate.get()).SetZTranslation(0.);
    translate.get()->SetSourceModule(0, *norm_lp_q.get());

    ModulePtr scale_point = std::make_shared<noise::module::ScalePoint>();
    ((noise::module::ScalePoint&)*scale_point.get()).SetXScale(2.);
    ((noise::module::ScalePoint&)*scale_point.get()).SetYScale(2.);
    ((noise::module::ScalePoint&)*scale_point.get()).SetZScale(0.);
    scale_point.get()->SetSourceModule(0, *translate.get());

    ModulePtr scale_bias = std::make_shared<noise::module::ScaleBias>();
    ((noise::module::ScaleBias&)*scale_bias.get()).SetBias(min);
    ((noise::module::ScaleBias&)*scale_bias.get()).SetScale(1. - min);
    scale_bias.get()->SetSourceModule(0, *scale_point.get());

    ModulePtr clamp = std::make_shared<noise::module::Clamp>();
    ((noise::module::Clamp&)*clamp.get()).SetBounds(min, 1.);
    clamp.get()->SetSourceModule(0, *scale_bias.get());

    ModulePtr mg = std::make_shared<ModuleGroup>();
    ModuleGroup& mg_r = (ModuleGroup&)*mg.get();
    mg_r.modules.insert({ mg_r.output_id, makeReseedable(clamp) });
    mg_r.modules.insert({ "scale_bias",makeReseedable(scale_bias) });
    mg_r.modules.insert({ "scale_point",makeReseedable(scale_point) });
    mg_r.modules.insert({ "translate", makeReseedable(translate) });
    mg_r.modules.insert({ "norm_lp_q", makeReseedable(norm_lp_q) });

    return makeReseedable(mg);
}

Reseedable makePlaceholder(int seed,
                           int octaves,
                           double frequency,
                           double lacunarity,
                           double persistence,
                           noise::NoiseQuality quality)
{
    ModulePtr placeholder = std::make_shared<noise::module::Perlin>();
    ((noise::module::Perlin&)*placeholder.get()).SetSeed(seed);
    ((noise::module::Perlin&)*placeholder.get()).SetOctaveCount(octaves);
    ((noise::module::Perlin&)*placeholder.get()).SetFrequency(frequency);
    ((noise::module::Perlin&)*placeholder.get()).SetLacunarity(lacunarity);
    ((noise::module::Perlin&)*placeholder.get()).SetPersistence(persistence);
    ((noise::module::Perlin&)*placeholder.get()).SetNoiseQuality(quality);
    return makeReseedable(placeholder);
}
