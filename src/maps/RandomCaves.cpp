#include "MapGenerator.h"
#include "FeatureIterator.h"
#include "Features.h"
#include "Random.h"
#include "Utility.h"

namespace dungeon
{
namespace map
{

template <typename R>
bool insert(TileMap& tileMap, const Feature& feature,
        const Point& location,
        std::vector<Feature>& features,
        std::vector<std::function<Point(int,int)>>& transforms)
{
    R r(feature,location);

    if(insert(tileMap,r))
    {
        features.push_back(feature);
        transforms.push_back([=](int x, int y) { return r.transform({x,y}); });
        return true;
    }
    return false;
}

TileMap randomCaves(const FeatureOptions& options)
{
    auto width = options.width();
    auto height = options.height();
    auto iterations = options.iterations();

    TileMap tileMap(width,height);
    std::vector<Feature> features;
    std::vector<Feature> doors;
    std::vector<std::function<Point(int,int)>> transforms;
    // generate a dungeon according to the following algorithm

    // build a rectangular room in the middle of the map
    auto rect = rectangle(4,4);
    features.push_back(rect);
    RF r(rect,{width/2,height/2});
    transforms.push_back([=](int x, int y) { return r.transform({x,y}); });
    insert(tileMap,r);

    // iterate a large number of times
    for (auto i = 0U; i < iterations; i++)
    {
        // get a random feature from the list
        auto r = randomRange(0,features.size() - 1);
        auto& feature = features[r];

        // get a random edge of this feature
        auto location_modelspace = randomEdge(feature);
        // transform the location
        auto location = transforms[r](location_modelspace.first,
                location_modelspace.second);

        // we want to be 2 away so we have a single tile door
        Point right{location.first+1,location.second};
        Point left{location.first-1,location.second};
        Point above{location.first,location.second+1};
        Point below{location.first,location.second-1};
        Point place;

        // check around this item
        // check to the right
        if (tileMap.clear(right))
        {
            // we can go right
            place = right;
        }
        else if (tileMap.clear(left))
        {
            // we can go left
            place = left;
        }
        else if (tileMap.clear(above))
        {
            // we can go above
            place = above;
        }
        else if (tileMap.clear(below))
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
        if(insert<RF>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<RM>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<RT>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<LF>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<LM>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<LT>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<LZ>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<AF>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<AM>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<AT>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<AZ>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<BF>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<BM>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<BT>(tileMap,feature_new,place,features,transforms)) continue;
        if(insert<BZ>(tileMap,feature_new,place,features,transforms)) continue;
    }
    return tileMap;
}

}
}
