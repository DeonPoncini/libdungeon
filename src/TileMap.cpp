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

const Feature* TileMap::at(Point location) const
{
    return mTiles[index(location)];
}

bool TileMap::clear(Point location) const
{
    return bounds(location) && (mTiles[index(location)] == nullptr);
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

void TileMap::set(Point location, const Feature* feature)
{
    mTiles[index(location)] = feature;
}

}
