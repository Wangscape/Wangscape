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
    ModulePtr cc(new CornerCombinerBase(power));

    ModulePtr sb(new noise::module::ScaleBias);
    ((noise::module::ScaleBias*)sb.get())->SetBias(0.5);
    ((noise::module::ScaleBias*)sb.get())->SetScale(0.5);
    sb.get()->SetSourceModule(0, *cc.get());

    ModulePtr clamp(new noise::module::Clamp);
    ((noise::module::Clamp*)clamp.get())->SetBounds(0., 1.);
    clamp.get()->SetSourceModule(0, *sb.get());

    ModulePtr mg(new ModuleGroup);
    ((ModuleGroup*)mg.get())->modules.push_back(std::move(clamp));
    ((ModuleGroup*)mg.get())->modules.push_back(std::move(sb));
    ((ModuleGroup*)mg.get())->modules.push_back(std::move(cc));

    return mg;

}
