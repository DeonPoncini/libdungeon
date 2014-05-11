#include "CellOptions.h"

namespace dungeon
{
CellOptions::CellOptions() :
    mWidth(100),
    mHeight(100),
    mIterations(2),
    mInitialLifeChance(0.4f),
    mEdgesAlive(false),
    mDeathLimit(2),
    mRebirthLimit(3)
{
}

CellOptions& CellOptions::size(unsigned width, unsigned height)
{
    mWidth = width;
    mHeight = height;
    return *this;
}

CellOptions& CellOptions::iterations(unsigned iterations)
{
    mIterations = iterations;
    return *this;
}

CellOptions& CellOptions::initialLifeChance(float chance)
{
    mInitialLifeChance = chance;
    return *this;
}

CellOptions& CellOptions::edgesAlive(bool alive)
{
    mEdgesAlive = alive;
    return *this;
}

CellOptions& CellOptions::deathLimit(unsigned limit)
{
    mDeathLimit = limit;
    return *this;
}

CellOptions& CellOptions::rebirthLimit(unsigned limit)
{
    mRebirthLimit = limit;
    return *this;
}

}
