#ifndef DUNGEON_MAPGENERATOR_H
#define DUNGEON_MAPGENERATOR_H

#include "TileMap.h"
#include "CellOptions.h"
#include "FeatureOptions.h"

namespace dungeon
{

namespace map
{

TileMap classic(const FeatureOptions& options);

TileMap randomCaves(const FeatureOptions& options);

TileMap conway(const CellOptions& options);

}
}

#endif
