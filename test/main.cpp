#include <iostream>

#include "FeatureIterator.h"
#include "Features.h"
#include "TileMap.h"
#include "Generator.h"
#include "DungeonOptions.h"

void print(const dungeon::TileMap& tileMap, const dungeon::Point& p)
{
    // print the map out
    auto width = tileMap.width();
    auto height = tileMap.height();
    for (auto y = 0U; y < height; y++)
    {
        for (auto x = 0U; x < width; x++)
        {
            if (x == static_cast<unsigned>(p.first) &&
                y == static_cast<unsigned>(p.second))
            {
                std::cout << "*";
                continue;
            }
            if (tileMap.at({x,y}) == nullptr)
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
    dungeon::DungeonOptions options;
    options.addFeature(dungeon::corridor);
    options.addFeature(dungeon::diamond);
    options.addFeature(dungeon::octogon);
    options.addFeature(dungeon::rectangle);
    options.addFeature(dungeon::trapezium);

    // generate the dungeon
    auto tileMap = dungeon::generate(options);
    print(tileMap,{0,0});

    return 0;
}
