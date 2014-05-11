#include "MapGenerator.h"
#include "Random.h"

namespace dungeon
{
namespace map
{

int aliveNeighbors(const TileMap& tileMap, bool aliveEdges, int x, int y)
{
    auto count = 0;
    for (auto i = -1; i < 2; i++)
    {
        for (auto j = -1; j < 2; j++)
        {
            auto nx = x + i;
            auto ny = y + j;
            // don't count our actual point
            if (i == 0 && j == 0) continue;
            // check boundaries
            if (nx < 0 || ny < 0 ||
                    nx >= tileMap.width() || ny >= tileMap.height())
            {
                if (aliveEdges)
                {
                    count++;
                }
            }
            else if (tileMap.at({nx,ny}).valid())
            {
                count++;
            }
        }
    }
    return count;
}

TileMap conway(const CellOptions& options)
{
    auto width = options.width();
    auto height = options.height();
    auto initialLifeChance = options.initialLifeChance();
    auto edgesAreAlive = options.edgesAlive();
    auto iterations = options.iterations();
    auto deathLimit = options.deathLimit();
    auto rebirthLimit = options.rebirthLimit();

    TileMap tileMap(width,height);

    // load up the tilemap, randomly make things live or dead
    for (auto x = 0; x < tileMap.width(); x++)
    {
        for (auto y = 0; y < tileMap.height(); y++)
        {
            if (randomRange(0.0f,1.0f) < initialLifeChance)
            {
                tileMap.set({x,y},Cell(true));
            }
        }
    }

    // run the game of life simulation
    auto newMap = tileMap;
    for (auto i = 0; i < iterations; i++)
    {
        // we make a copy every time so we calculate correctly
        newMap = TileMap(tileMap.width(),tileMap.height());
        for (auto x = 0; x < tileMap.width(); x++)
        {
            for (auto y = 0; y < tileMap.height(); y++)
            {
                auto alive = aliveNeighbors(tileMap,edgesAreAlive,x,y);

                // if a cell is alive but too few neighbors, kill it
                Point p{x,y};
                if (tileMap.at(p).valid())
                {
                    if (alive < deathLimit)
                    {
                        newMap.set(p,Cell());
                    }
                    else
                    {
                        newMap.set(p,Cell(true));
                    }
                }
                // if a cell is dead, check if it has enough neighbors to
                // be reborn
                else
                {
                    if (alive > rebirthLimit)
                    {
                        newMap.set(p,Cell(true));
                    }
                    else
                    {
                        newMap.set(p,Cell());
                    }
                }
            }
        }
    }

    return newMap;
}

}
}
