#pragma once
#include <memory>
class ReseedableBase;

namespace noise
{
namespace module
{

typedef std::shared_ptr<ReseedableBase> ReseedablePtr;

} // namespace noise
} // namespace module
