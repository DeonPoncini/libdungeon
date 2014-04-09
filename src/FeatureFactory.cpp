#include "FeatureFactory.h"

#include "Feature.h"
#include "Random.h"

#include <stdexcept>
#include <sstream>

namespace dungeon
{

void FeatureFactory::addFeature(std::string name, FeatureFunction function)
{
    mFeatures.emplace(std::move(name),function);
}

Feature FeatureFactory::create(
        const std::string& name, int width, int height) const
{
   auto f = mFeatures.find(name);
   if (f != mFeatures.end())
   {
        return f->second(width,height);
   }
   std::stringstream ss;
   ss << "Feature name " << name << " not found";
   throw std::out_of_range(ss.str());
}

Feature FeatureFactory::createRandom(
        int minW, int maxW, int minH, int maxH) const
{
    // make up a random width and height
    auto w = randomRange(minW,maxW);
    auto h = randomRange(minH,maxH);
    auto f = randomRange(0,mFeatures.size() - 1);
    auto i = 0;
    for(auto&& kv : mFeatures)
    {
        if (i == f)
        {
            return kv.second(w,h);
        }
        ++i;
    }
    throw std::runtime_error("Range not within size");
}

}
