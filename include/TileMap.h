#ifndef DUNGEON_TILEMAP_H
#define DUNGEON_TILEMAP_H

#include "Types.h"
#include "Cell.h"

namespace dungeon
{

class TileMap
{
public:
    TileMap(unsigned width, unsigned height);

    Cell at(Point location) const;
    void set(Point location, Cell cell);

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

    int index(Point location) const;

};

}

#endif
