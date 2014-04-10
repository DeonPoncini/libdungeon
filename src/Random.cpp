#include "Random.h"
#include "Feature.h"

#include <random>

namespace dungeon
{

int randomRange(int start, int end)
{
    static std::random_device device;
    static std::mt19937 gen(device());
    std::uniform_int_distribution<> dist(start,end);
    return dist(gen);
}

Point randomEdge(const Feature& feature)
{
    // select a random row
    auto y = randomRange(0,feature.height() - 1);
    auto offset = feature.offset(y);
    auto width = feature.width(y);
    auto x = offset;
    // special case, row is first or last
    if (y == 0 || y == feature.height() - 1)
    {
        // pick somewhere along this edge
        x = randomRange(offset,offset + width - 1);
    }
    else
    {
        // either first or last position in the row
        auto flip = randomRange(0,1);
        if (flip == 0)
        {
            x = offset + width - 1;
        }
    }
    return {x,y};
}

}
