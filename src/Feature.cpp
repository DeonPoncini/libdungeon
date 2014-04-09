#include "Feature.h"

namespace dungeon
{

Feature::Feature(EdgeList edges) :
    mEdges(std::move(edges))
{
}

}
