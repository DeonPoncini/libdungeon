#ifndef DUNGEON_RANDOM_H
#define DUNGEON_RANDOM_H

#include "Types.h"

namespace dungeon
{
class Feature;

int randomRange(int start, int end);
Point randomEdge(const Feature& feature);

}

#endif
