#ifndef DUNGEON_TILEMAP_H
#define DUNGEON_TILEMAP_H

#include "Types.h"
#include "Feature.h"

namespace dungeon
{

class TileMap
{
public:
    TileMap(unsigned width, unsigned height);

    Feature* at(Point location) const;

    template <typename FI>
    bool insert(Feature* feature, FI iterator);

    inline unsigned width() const { return mWidth; }
    inline unsigned height() const { return mHeight; }

private:
    unsigned mWidth;
    unsigned mHeight;
    unsigned mSize;
    unsigned mStride;

    std::vector<Feature*> mTiles;

    bool clearAround(Point location) const;
    bool clear(Point location) const;

    template <typename FI>
    bool clear(Feature* feature, FI iterator);

    int index(Point location) const;
    void set(Point location, Feature* feature);

};

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

    for (auto y = iterator.begin(); y != iterator.end(); y = iterator.next())
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
    for (auto y = iterator.begin(); y != iterator.end(); y = iterator.next())
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

}

#endif
