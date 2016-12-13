#include "ModuleFactories.h"
#include "Gradient.h"

ModulePtr makePeak(bool x)
{
    ModulePtr gradient;
    if (x)
        gradient.reset(new GradientX);
    else
        gradient.reset(new GradientY);

    ModulePtr abs(new noise::module::Abs);
    abs.get()->SetSourceModule(0, *gradient.get());

    ModulePtr inv(new noise::module::Invert);
    inv.get()->SetSourceModule(0, *abs.get());

    ModulePtr one(new noise::module::Const);
    ((noise::module::Const*)one.get())->SetConstValue(1.);

    ModulePtr add(new noise::module::Add);
    add.get()->SetSourceModule(0, *one.get());
    add.get()->SetSourceModule(1, *inv.get());

    ModulePtr mg(new ModuleGroup);
    ((ModuleGroup*)mg.get())->modules.push_back(std::move(add));
    ((ModuleGroup*)mg.get())->modules.push_back(std::move(one));
    ((ModuleGroup*)mg.get())->modules.push_back(std::move(inv));
    ((ModuleGroup*)mg.get())->modules.push_back(std::move(abs));
    ((ModuleGroup*)mg.get())->modules.push_back(std::move(gradient));

    return mg;
}

ModulePtr makeCornerCombiner(bool x_positive, bool y_positive, double power)
{
    ModulePtr mg = std::make_shared<ModuleGroup>();
    ModuleGroup& mg_r = (ModuleGroup&)*mg.get();

    mg_r.modules.push_back(std::make_shared<noise::module::Clamp>());
    ModulePtr clamp = mg_r.modules[0];

    mg_r.modules.push_back(std::make_shared<noise::module::ScaleBias>());
    ModulePtr scale_bias = mg_r.modules[1];

    mg_r.modules.push_back(std::make_shared<CornerCombinerBase>(power));
    ModulePtr corner_combiner_base = mg_r.modules[2];

    ((noise::module::ScaleBias&)*scale_bias.get()).SetBias(0.5);
    ((noise::module::ScaleBias&)*scale_bias.get()).SetScale(0.5);
    scale_bias.get()->SetSourceModule(0, *corner_combiner_base.get());

    ((noise::module::Clamp&)*clamp.get()).SetBounds(0., 1.);
    clamp.get()->SetSourceModule(0, *scale_bias.get());


    return mg;

}
