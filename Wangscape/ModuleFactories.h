#pragma once
#include "ModuleGroup.h"

// Makes a ModuleGroup with values 1-|x| or 1-|y|.
ModuleGroup::ModulePtr makePeak(bool x);

//ModuleGroup::ModulePtr makeQuadrantSelector(bool x,  bool y)