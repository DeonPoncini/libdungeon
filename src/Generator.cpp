#include "Generator.h"

#include "Features.h"
#include "Feature.h"
#include "FeatureIterator.h"
#include "Random.h"
#include "DungeonOptions.h"

#include <vector>

#include <iostream>

namespace dungeon
{

TileMap generate(const DungeonOptions& options)
{
    auto width = options.mWidth;
    auto height = options.mHeight;

    TileMap tileMap(width,height);
    std::vector<Feature> features;
    std::vector<Feature> doors;
    std::vector<std::function<Point(int,int)>> transforms;
    // generate a dungeon according to the following algorithm

    // build a rectangular room in the middle of the map
    auto rect = rectangle(4,4);
    features.push_back(rect);
    RF r(rect,{width/2,height/2});
    transforms.push_back([=](int x, int y) { return r(x,y); });
    tileMap.insert(&rect,r);

    // iterate a large number of times
    for (auto i = 0; i < 10; i++)
    {
        // get a random feature from the list
        auto r = randomRange(0,features.size() - 1);
        auto& feature = features[r];

        // get a random edge of this feature
        auto location_modelspace = randomEdge(feature);
        std::cout << "Modelspace: " << location_modelspace.first <<
            ", " << location_modelspace.second << std::endl;
        // transform the location
        auto location = transforms[r](location_modelspace.first,
                location_modelspace.second);
        std::cout << "Location: " << location.first <<
            ", " << location.second << std::endl;

        // we want to be 2 away so we have a single tile door
        Point right{location.first+2,location.second};
        Point left{location.first-2,location.second};
        Point above{location.first,location.second+2};
        Point below{location.first,location.second-2};
        Point place;

        // check around this item
        // check to the right
        if (tileMap.clearAround(right))
        {
            // we can go right
            place = right;
        }
        else if(tileMap.clearAround(left))
        {
            // we can go left
            place = left;
        }
        else if(tileMap.clearAround(above))
        {
            // we can go above
            place = above;
        }
        else if(tileMap.clearAround(below))
        {
            // we can go below
            place = below;
        }
        else
        {
            // this object can't fit here, go to next iteration
            continue;
        }

        // create a new feature
        auto feature_new = options.createRandom();
        // try every orientation
        {
            std::cout << "Place: " << place.first << ", " << place.second
                << std::endl;
            RF r(feature_new,place);

            if(tileMap.insert(&feature_new,r))
            {
                features.push_back(feature_new);
                transforms.push_back([=](int x, int y) { return r(x,y); });
            }
        }
#if 0
        if(tileMap.insert(&feature,RM(feature,place))) continue;
        if(tileMap.insert(&feature,RT(feature,place))) continue;
        if(tileMap.insert(&feature,RZ(feature,place))) continue;
        if(tileMap.insert(&feature,LF(feature,place))) continue;
        if(tileMap.insert(&feature,LM(feature,place))) continue;
        if(tileMap.insert(&feature,LT(feature,place))) continue;
        if(tileMap.insert(&feature,LZ(feature,place))) continue;
        if(tileMap.insert(&feature,AF(feature,place))) continue;
        if(tileMap.insert(&feature,AM(feature,place))) continue;
        if(tileMap.insert(&feature,AT(feature,place))) continue;
        if(tileMap.insert(&feature,AZ(feature,place))) continue;
        if(tileMap.insert(&feature,BF(feature,place))) continue;
        if(tileMap.insert(&feature,BM(feature,place))) continue;
        if(tileMap.insert(&feature,BT(feature,place))) continue;
        if(tileMap.insert(&feature,BZ(feature,place))) continue;
#endif

    }
    return tileMap;
}

}
