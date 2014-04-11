#include "DungeonOptions.h"

#include "Feature.h"
#include "Random.h"

namespace dungeon
{

DungeonOptions::DungeonOptions() :
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

DungeonOptions& DungeonOptions::setSize(unsigned width, unsigned height)
{
    mWidth = width;
    mHeight = height;
    return *this;
}

DungeonOptions& DungeonOptions::addFeature(FeatureFunction function,
        double weight)
{
    mFeatures.emplace_back(function);
    mIntervals.push_back(mIntervals.size());
    mWeights.push_back(weight);
    return *this;
}

DungeonOptions& DungeonOptions::setMinWidth(int width)
{
    mMinW = width;
    return *this;
}

DungeonOptions& DungeonOptions::setMaxWidth(int width)
{
    mMaxW = width;
    return *this;
}

DungeonOptions& DungeonOptions::setMinHeight(int height)
{
    mMinH = height;
    return *this;
}

DungeonOptions& DungeonOptions::setMaxHeight(int height)
{
    mMaxH = height;
    return *this;
}

DungeonOptions& DungeonOptions::setIterations(unsigned iterations)
{
    mIterations = iterations;
    return *this;
}

Feature DungeonOptions::createRandom() const
{
    // make up a random width and height
    auto w = randomRange(mMinW,mMaxW);
    auto h = randomRange(mMinH,mMaxH);
    auto f = weightedRoll(mIntervals,mWeights);
    return mFeatures[f](w,h);
}

}
