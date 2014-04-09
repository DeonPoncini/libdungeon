#include "FeatureFactory.h"

#include "Feature.h"
#include "Random.h"

namespace dungeon
{

void FeatureFactory::addFeature(FeatureFunction function)
{
    mFeatures.emplace_back(function);
}

Feature FeatureFactory::createRandom(
        int minW, int maxW, int minH, int maxH) const
{
    // make up a random width and height
    auto w = randomRange(minW,maxW);
    auto h = randomRange(minH,maxH);
    auto f = randomRange(0,mFeatures.size() - 1);
    return mFeatures[f](w,h);
}

}
