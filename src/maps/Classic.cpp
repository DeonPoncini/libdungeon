#include "FeatureIterator.h"
#include "Features.h"
#include "MapGenerator.h"
#include "Random.h"
#include "Utility.h"

namespace dungeon
{
namespace map
{

TileMap classic(const FeatureOptions& options)
{
    auto width = options.width();
    auto height = options.height();
    auto iterations = options.iterations();

    TileMap tileMap(width,height);

    Point lastLocation{-1,-1};
    for (auto i = 0U; i < iterations; i++)
    {
        // select a random location
        auto x = randomRange(0,width - 1);
        auto y = randomRange(0,height - 1);

        // build a random room
        auto feature = options.createRandom();
        Point location(x,y);
        RF rf(feature,location);
        if (insert(tileMap,rf))
        {
            if(lastLocation.first != -1)
            {
                auto xlength = std::abs(location.first - lastLocation.first);
                auto ylength = std::abs(location.second - lastLocation.second);
                Point yStartPoint;
                // horizontal corridor
                if (location.first >= lastLocation.first)
                {
                    auto cx = corridor(xlength);
                    LM cr(cx,location);
                    yStartPoint = {location.first - xlength, location.second};
                    forceInsert(tileMap,cr);
                }
                else
                {
                    auto cx = corridor(xlength);
                    yStartPoint = {location.first + xlength, location.second};
                    RF cr(cx,location);
                    forceInsert(tileMap,cr);
                }
                // vertical corridor
                if (location.second >= lastLocation.second)
                {
                    auto cy = corridor(ylength);
                    AT cr(cy,yStartPoint);
                    forceInsert(tileMap,cr);
                }
                else
                {
                    auto cy = corridor(ylength);
                    BZ cr(cy,yStartPoint);
                    forceInsert(tileMap,cr);
                }
            }
            lastLocation = location;
        }
    }
    return tileMap;
}

}
}
