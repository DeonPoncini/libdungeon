#include "FeatureOptions.h"

#include "Feature.h"
#include "Random.h"

namespace dungeon
{

FeatureOptions::FeatureOptions() :
    mWidth(100),
    mHeight(100),
    mMinW(4),
    mMaxW(10),
    mMinH(4),
    mMaxH(10),
    mIterations(1000)
{
    mIntervals.push_back(0.0);
}

FeatureOptions& FeatureOptions::size(unsigned width, unsigned height)
{
    mWidth = width;
    mHeight = height;
    return *this;
}

FeatureOptions& FeatureOptions::addFeature(FeatureFunction function,
        double weight)
{
    mFeatures.emplace_back(function);
    mIntervals.push_back(mIntervals.size());
    mWeights.push_back(weight);
    return *this;
}

FeatureOptions& FeatureOptions::minWidth(int width)
{
    mMinW = width;
    return *this;
}

FeatureOptions& FeatureOptions::maxWidth(int width)
{
    mMaxW = width;
    return *this;
}

FeatureOptions& FeatureOptions::minHeight(int height)
{
    mMinH = height;
    return *this;
}

FeatureOptions& FeatureOptions::maxHeight(int height)
{
    mMaxH = height;
    return *this;
}

FeatureOptions& FeatureOptions::iterations(unsigned iterations)
{
    mIterations = iterations;
    return *this;
}

Feature FeatureOptions::createRandom() const
{
    // make up a random width and height
    auto w = randomRange(mMinW,mMaxW);
    auto h = randomRange(mMinH,mMaxH);
    auto f = weightedRoll(mIntervals,mWeights);
    return mFeatures[f](w,h);
}

}
