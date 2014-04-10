#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#include "TileMap.h"

namespace dungeon
{

class DungeonOptions;

TileMap generate(const DungeonOptions& options);

}

#endif
