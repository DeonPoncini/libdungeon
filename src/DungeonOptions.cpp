#include "DungeonOptions.h"

#include "Feature.h"
#include "Random.h"

namespace dungeon
{

DungeonOptions::DungeonOptions() :
    mWidth(100),
    mHeight(100),
    mMinW(2),
    mMaxW(10),
    mMinH(2),
    mMaxH(10)
{
}

DungeonOptions& DungeonOptions::setSize(unsigned width, unsigned height)
{
    mWidth = width;
    mHeight = height;
    return *this;
}

DungeonOptions& DungeonOptions::addFeature(FeatureFunction function)
{
    mFeatures.emplace_back(function);
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

Feature DungeonOptions::createRandom() const
{
    // make up a random width and height
    auto w = randomRange(mMinW,mMaxW);
    auto h = randomRange(mMinH,mMaxH);
    auto f = randomRange(0,mFeatures.size() - 1);
    return mFeatures[f](w,h);
}

}
