#ifndef DUNGEON_TYPES_H
#define DUNGEON_TYPES_H

#include <utility>
#include <vector>

namespace dungeon
{
typedef std::pair<int,int> Edge;
typedef std::vector<Edge> EdgeList;
typedef std::pair<unsigned,unsigned> Point;
}

#endif
