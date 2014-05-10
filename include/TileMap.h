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

    const Feature* at(Point location) const;

    template <typename FI>
    bool insert(FI iterator);
    bool clear(Point location) const;

    inline unsigned width() const { return mWidth; }
    inline unsigned height() const { return mHeight; }

private:
    unsigned mWidth;
    unsigned mHeight;
    unsigned mSize;
    unsigned mStride;

    std::vector<const Feature*> mTiles;

    bool bounds(Point location) const;

    template <typename FI>
    bool isClear(FI iterator);

    int index(Point location) const;
    void set(Point location, const Feature* feature);

};

template <typename FI>
bool TileMap::insert(FI iterator)
{
    if (!isClear(iterator))
    {
        return false;
    }

    for (auto&& row : iterator)
    {
        for (auto&& point : row)
        {
            set(point,*iterator);
        }
    }
    return true;
}

template <typename FI>
bool TileMap::isClear(FI iterator)
{
    for (auto&& row : iterator)
    {
        for (auto&& point : row)
        {
            if (!clear(point))
            {
                return false;
            }
        }
    }
    return true;
}

}

#endif
