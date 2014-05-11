#include "Cell.h"

namespace dungeon
{

Cell::Cell() :
    mValid(0)
{
}

Cell::Cell(bool valid) :
    mValid(static_cast<unsigned char>(valid))
{
}

}
