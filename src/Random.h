#ifndef DUNGEON_RANDOM_H
#define DUNGEON_RANDOM_H

#include "Types.h"

namespace dungeon
{
class Feature;

int randomRange(int start, int end);
int weightedRoll(const std::vector<double>& intervals,
        const std::vector<double>& weights);

Point randomEdge(const Feature& feature);

}

#endif
