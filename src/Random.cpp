#include "Random.h"
#include "Feature.h"

#include <random>

namespace dungeon
{

std::mt19937& generator()
{
    static std::random_device device;
    static std::mt19937 gen(device());
    return gen;
}

int randomRange(int start, int end)
{
    std::uniform_int_distribution<> dist(start,end);
    return dist(generator());
}

float randomRange(float start, float end)
{
    std::uniform_real_distribution<> dist(start,end);
    return dist(generator());
}

int weightedRoll(const std::vector<double>& intervals,
        const std::vector<double>& weights)
{
    std::piecewise_constant_distribution<double> dist(
            std::begin(intervals),std::end(intervals),
            std::begin(weights));
    return dist(generator());
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
