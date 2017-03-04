#include "QuadrantSelector.h"

namespace noise
{
namespace module
{

QuadrantSelector::QuadrantSelector() :
    TranslatePoint(),
    mTranslate{
        DEFAULT_QUADRANT_SELECTOR_TRANSLATE,
        DEFAULT_QUADRANT_SELECTOR_TRANSLATE,
        DEFAULT_QUADRANT_SELECTOR_TRANSLATE},
    mTranslateIgnored{
        DEFAULT_QUADRANT_SELECTOR_TRANSLATE_IGNORED,
        DEFAULT_QUADRANT_SELECTOR_TRANSLATE_IGNORED,
        DEFAULT_QUADRANT_SELECTOR_TRANSLATE_IGNORED}
{
    UpdateTranslation();
}

void QuadrantSelector::SetTranslate(size_t dimension, bool translate)
{
    if (dimension > 2)
    {
        throw std::out_of_range("Tried to set QuadrantSelector translation with dimension greater than 2");
    }
    mTranslate[dimension] = translate;
    UpdateTranslation();
}

void QuadrantSelector::SetTranslate(bool x_translate, bool y_translate, bool z_translate)
{
    mTranslate = {x_translate, y_translate, z_translate};
    UpdateTranslation();
}

bool QuadrantSelector::GetTranslate(size_t dimension) const
{
    if (dimension > 2)
    {
        throw std::out_of_range("Tried to set QuadrantSelector translation with dimension greater than 2");
    }
    return mTranslate[dimension];
}

void QuadrantSelector::SetTranslateIgnored(size_t dimension, bool translate_ignored)
{
    if (dimension > 2)
    {
        throw std::out_of_range("Tried to set QuadrantSelector translation with dimension greater than 2");
    }
    mTranslateIgnored[dimension] = translate_ignored;
    UpdateTranslation();
}

void QuadrantSelector::SetTranslateIgnored(bool x_translate_ignored, bool y_translate_ignored, bool z_translate_ignored)
{
    mTranslateIgnored = {x_translate_ignored, y_translate_ignored, z_translate_ignored};
    UpdateTranslation();
}

bool QuadrantSelector::GetTranslateIgnored(size_t dimension) const
{
    if (dimension > 2)
    {
        throw std::out_of_range("Tried to ignore/unignore QuadrantSelector translation with dimension greater than 2");
    }
    return mTranslateIgnored[dimension];
}

void QuadrantSelector::UpdateTranslation()
{
    TranslatePoint::SetXTranslation((mTranslate[0] && !mTranslateIgnored[0]) ? -1. : 0.);
    TranslatePoint::SetYTranslation((mTranslate[1] && !mTranslateIgnored[1]) ? -1. : 0.);
    TranslatePoint::SetZTranslation((mTranslate[2] && !mTranslateIgnored[2]) ? -1. : 0.);
}

} // namespace module
} // namespace noise
