#include <iostream>

#include "Feature.h"
#include "Features.h"
#include "TileMap.h"
#include "MapGenerator.h"
#include "FeatureOptions.h"
#include "CellOptions.h"

void print(const dungeon::TileMap& tileMap)
{
    // print the map out
    auto width = tileMap.width();
    auto height = tileMap.height();
    for (auto y = 0U; y < height; y++)
    {
        for (auto x = 0U; x < width; x++)
        {
            if (!tileMap.at({x,y}).valid())
            {
                std::cout << ' ';
            }
            else
            {
                std::cout << '#';
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    dungeon::FeatureOptions options;
    options.addFeature(dungeon::rectangle);
    options.addFeature(dungeon::octogon);
    options.addFeature(dungeon::trapezium);
    options.addFeature(dungeon::triangle);
    options.iterations(20);
    auto tileMap = dungeon::map::classic(options);
    print(tileMap);
    options.iterations(1000);
    auto tileMap2 = dungeon::map::randomCaves(options);
    print(tileMap2);
    auto tileMap3 = dungeon::map::conway(dungeon::CellOptions());
    print(tileMap3);

    return 0;
}
