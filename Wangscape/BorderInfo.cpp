#include "BorderInfo.h"
#include <noise/noise.h>



BorderInfo::BorderInfo(const Options& options)
{
    for (const auto& clique : options.cliques)
    {
        for (const auto& t1 : clique)
        {
            for (const auto& t2 : clique)
            {
                //UniqueModule border_x = (UniqueModule)std::make_unique<noise::module::Perlin>();
                //((std::unique_ptr<noise::module::Perlin>)border_x)->SetSeed(rand());

                //UniqueModule border_y = (UniqueModule)std::make_unique<noise::module::Perlin>();
                //((std::unique_ptr<noise::module::Perlin>)border_y)->SetSeed(rand());

                //borders.insert({ { t1,t2 }, {border_x, border_y} });
            }
        }
    }
}


BorderInfo::~BorderInfo()
{
}

noise::module::ScalePoint BorderInfo::flatten_x() const
{
    noise::module::ScalePoint r;
    r.SetYScale(0.0);
    return r;
}

noise::module::ScalePoint BorderInfo::flatten_y() const
{
    noise::module::ScalePoint r;
    r.SetXScale(0.0);
    return r;
}
