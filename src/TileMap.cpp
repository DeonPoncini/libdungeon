#include "TileMap.h"

namespace dungeon
{

TileMap::TileMap(unsigned width, unsigned height) :
    mWidth(width),
    mHeight(height),
    mSize(mWidth*mHeight),
    mStride(mWidth),
    mTiles(mSize,nullptr)
{
}

Feature* TileMap::at(Point location) const
{
    return mTiles[index(location)];
}

bool TileMap::clearAround(Point location) const
{
    // check the point is in bounds
    if (!bounds(location)) return false;
    // check the point itself is clear
    if (!clear(location)) return false;
    // check the points around it to make sure they are clear
    Point p1(location.first + 1, location.second);
    Point p2(location.first - 1, location.second);
    Point p3(location.first,location.second + 1);
    Point p4(location.first,location.second - 1);

    if (bounds(p1) && !clear(p1)) return false;
    if (bounds(p2) && !clear(p2)) return false;
    if (bounds(p3) && !clear(p3)) return false;
    if (bounds(p4) && !clear(p4)) return false;
    return true;
}

bool TileMap::clear(Point location) const
{
    return mTiles[index(location)] == nullptr;
}

bool TileMap::bounds(Point location) const
{
    if (location.first < 0) return false;
    if (location.second < 0) return false;
    if (location.first >= static_cast<int>(mWidth)) return false;
    if (location.second >= static_cast<int>(mHeight)) return false;
    return true;
}

int TileMap::index(Point location) const
{
    return location.second*mStride + location.first;
}

void TileMap::set(Point location, Feature* feature)
{
    mTiles[index(location)] = feature;
}

}
