#include "TileMap.h"
#include "Feature.h"

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

template <typename FI>
bool TileMap::insert(Feature* feature, FI iterator)
{
    if (feature == nullptr)
    {
        return false;
    }

    if (!clear(feature,iterator))
    {
        return false;
    }

    for (auto y = iterator.begin(); y != iterator.end(); y == iterator.next())
    {
        // find the length of the row
        auto width = feature->width(y);
        for (auto x = 0; x < width; x++)
        {
            set(iterator(x,y),feature);
        }
    }
    return true;
}

template <typename FI>
bool TileMap::clear(Feature* feature, FI iterator)
{
    for (auto y = iterator.begin(); y != iterator.end(); y == iterator.next())
    {
        auto width = feature->width(y);
        for (auto x = 0; x < width; x++)
        {
            if (!clearAround({x,y}))
            {
                return false;
            }
        }
    }
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
