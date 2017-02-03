#include "WrapperBase.h"
#include <stdexcept>

namespace noise
{
namespace module
{

void WrapperBase::setSourceModule(int index, const Module & source_module)
{
    getModule().SetSourceModule(index, source_module);
}

double WrapperBase::getValue(double x, double y, double z) const
{
    return getModule().GetValue(x, y, z);
}

} // namespace module

} // namespace noise
