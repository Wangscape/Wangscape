#include "ModuleFactories.h"
#include "Gradient.h"
#include "NormLPQ.h"

ModulePtr makePeak(bool x)
{
    ModulePtr gradient;
    if (x)
        gradient = std::make_shared<GradientX>();
    else
        gradient = std::make_shared<GradientY>();

    ModulePtr abs = std::make_shared<noise::module::Abs>();
    abs.get()->SetSourceModule(0, *gradient.get());

    ModulePtr inv = std::make_shared<noise::module::Invert>();
    inv.get()->SetSourceModule(0, *abs.get());

    ModulePtr one = std::make_shared<noise::module::Const>();
    ((noise::module::Const*)one.get())->SetConstValue(1.);

    ModulePtr add = std::make_shared<noise::module::Add>();
    add.get()->SetSourceModule(0, *one.get());
    add.get()->SetSourceModule(1, *inv.get());

    ModulePtr mg(new ModuleGroup);
    ModuleGroup& mg_r = (ModuleGroup&)*mg.get();
    mg_r.modules.push_back(add);
    mg_r.modules.push_back(one);
    mg_r.modules.push_back(inv);
    mg_r.modules.push_back(abs);
    mg_r.modules.push_back(gradient);

    return mg;
}

ModulePtr makeCornerCombiner(bool x_positive, bool y_positive, double power)
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
    mg_r.modules.push_back(clamp);
    mg_r.modules.push_back(scale_bias);
    mg_r.modules.push_back(corner_combiner_base);

    return mg;

}

ModulePtr makeEdgeFavouringMask(double p, double q)
{
    ModulePtr norm_lp_q = std::make_shared<NormLPQ>(p, q);

    ModulePtr translate = std::make_shared<noise::module::TranslatePoint>();
    ((noise::module::TranslatePoint&)*translate.get()).SetXTranslation(-1.);
    ((noise::module::TranslatePoint&)*translate.get()).SetYTranslation(-1.);
    ((noise::module::TranslatePoint&)*translate.get()).SetZTranslation(0.);
    translate.get()->SetSourceModule(0, *norm_lp_q.get());

    ModulePtr scale = std::make_shared<noise::module::ScalePoint>();
    ((noise::module::ScalePoint&)*scale.get()).SetXScale(2.);
    ((noise::module::ScalePoint&)*scale.get()).SetYScale(2.);
    ((noise::module::ScalePoint&)*scale.get()).SetZScale(0.);
    scale.get()->SetSourceModule(0, *translate.get());

    ModulePtr clamp = std::make_shared<noise::module::Clamp>();
    ((noise::module::Clamp&)*clamp.get()).SetBounds(0., 1.);
    clamp.get()->SetSourceModule(0, *scale.get());

    ModulePtr mg = std::make_shared<ModuleGroup>();
    ModuleGroup& mg_r = (ModuleGroup&)*mg.get();
    mg_r.modules.push_back(clamp);
    mg_r.modules.push_back(scale);
    mg_r.modules.push_back(translate);
    mg_r.modules.push_back(norm_lp_q);
    return mg;
}
