#pragma once
#include <noise/noise.h>
#include <array>

namespace noise
{
namespace module
{


const static bool DEFAULT_QUADRANT_SELECTOR_TRANSLATE = false;
const static bool DEFAULT_QUADRANT_SELECTOR_TRANSLATE_IGNORED = false;

class QuadrantSelector : public TranslatePoint
{
public:
    QuadrantSelector();
    void SetTranslate(size_t dimension, bool translate);
    void SetTranslate(bool x_translate, bool y_translate, bool z_translate);
    bool GetTranslate(size_t dimension) const;

    void SetTranslateIgnored(size_t dimension, bool translate_ignored);
    void SetTranslateIgnored(bool x_translate_ignored, bool y_translate_ignored, bool z_translate_ignored);
    bool GetTranslateIgnored(size_t dimension) const;

private:
    void UpdateTranslation();
    std::array<bool, 3> mTranslate;
    std::array<bool, 3> mTranslateIgnored;
    using TranslatePoint::SetXTranslation;
    using TranslatePoint::SetYTranslation;
    using TranslatePoint::SetZTranslation;
    using TranslatePoint::SetTranslation;
};

} // namespace module
} // namespace noise
