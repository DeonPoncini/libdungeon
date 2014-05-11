#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#include "TileMap.h"

namespace dungeon
{
class DungeonOptions;
namespace generate
{

TileMap classic(const DungeonOptions& options);

TileMap randomCaves(const DungeonOptions& options);

TileMap conway();

}
}

#endif
