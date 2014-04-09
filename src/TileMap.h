#ifndef DUNGEON_TILEMAP_H
#define DUNGEON_TILEMAP_H

#include "Types.h"

namespace dungeon
{

class Feature;

class TileMap
{
public:
    TileMap(unsigned width, unsigned height);

    Feature* at(Point location) const;

    template <typename FI>
    bool insert(Feature* feature, FI iterator);

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

}

#endif
