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
    // check the location is in bounds
    Point p1(location.first < mWidth - 1? location.first + 1 : location.first,
            location.second);
    Point p2(location.first > 0 ? location.first - 1 : location.first,
            location.second);
    Point p3(location.first,location.second < mHeight - 1 ? location.second + 1:
            location.second);
    Point p4(location.first,location.second > 0 ? location.second - 1 :
            location.second);

    if (!clear(p1)) return false;
    if (!clear(p2)) return false;
    if (!clear(p3)) return false;
    if (!clear(p4)) return false;
    return true;
}

bool TileMap::clear(Point location) const
{
    return mTiles[index(location)] == nullptr;
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
