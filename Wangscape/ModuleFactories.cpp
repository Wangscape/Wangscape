#include "ModuleFactories.h"
#include "Gradient.h"

ModuleGroup::ModulePtr makePeak(bool x)
{
    ModuleGroup::ModulePtr gradient;
    if (x)
        gradient.reset(new GradientX);
    else
        gradient.reset(new GradientY);

    ModuleGroup::ModulePtr abs(new noise::module::Abs);
    abs.get()->SetSourceModule(0, *gradient.get());

    ModuleGroup::ModulePtr inv(new noise::module::Invert);
    inv.get()->SetSourceModule(0, *abs.get());

    ModuleGroup::ModulePtr one(new noise::module::Const);
    ((noise::module::Const*)one.get())->SetConstValue(1.);

    ModuleGroup::ModulePtr add(new noise::module::Add);
    add.get()->SetSourceModule(0, *one.get());
    add.get()->SetSourceModule(1, *inv.get());

    ModuleGroup::ModulePtr mg(new ModuleGroup);
    ((ModuleGroup*)mg.get())->modules.push_back(add);
    ((ModuleGroup*)mg.get())->modules.push_back(one);
    ((ModuleGroup*)mg.get())->modules.push_back(inv);
    ((ModuleGroup*)mg.get())->modules.push_back(abs);
    ((ModuleGroup*)mg.get())->modules.push_back(gradient);

    return mg;
}
