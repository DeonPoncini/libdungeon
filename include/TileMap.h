#ifndef DUNGEON_TILEMAP_H
#define DUNGEON_TILEMAP_H

#include "Types.h"
#include "Feature.h"
#include "Cell.h"

namespace dungeon
{

class TileMap
{
public:
    TileMap(unsigned width, unsigned height);

    Cell at(Point location) const;
    void set(Point location, Cell cell);

    template <typename FI>
    bool insert(FI iterator);
    template <typename FI>
    void forceInsert(FI iterator);
    bool clear(Point location) const;

    inline unsigned width() const { return mWidth; }
    inline unsigned height() const { return mHeight; }

private:
    unsigned mWidth;
    unsigned mHeight;
    unsigned mSize;
    unsigned mStride;

    std::vector<Cell> mTiles;

    bool bounds(Point location) const;

    template <typename FI>
    bool isClear(FI iterator);

    int index(Point location) const;

};

template <typename FI>
bool TileMap::insert(FI iterator)
{
    if (!isClear(iterator))
    {
        return false;
    }

    forceInsert(iterator);
    return true;
}

template <typename FI>
void TileMap::forceInsert(FI iterator)
{
    for (auto&& row : iterator)
    {
        for (auto&& point : row)
        {
            set(iterator.transform(point),
                    (*iterator)->at(point));
        }
    }
}

template <typename FI>
bool TileMap::isClear(FI iterator)
{
    for (auto&& row : iterator)
    {
        for (auto&& point : row)
        {
            if (!clear(iterator.transform(point)))
            {
                return false;
            }
        }
    }
    return true;
}

}

#endif
