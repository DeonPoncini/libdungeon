#include "Feature.h"

namespace dungeon
{

Feature::Feature(EdgeList edges) :
    mEdges(std::move(edges))
{
    mWidths.push_back(0);
    for (auto&& e : mEdges)
    {
        mWidths.push_back(e.second + mWidths.back());
        for (auto i = 0; i < e.second; i++)
        {
            mCells.emplace_back(Cell(true));
        }
    }
}

Cell Feature::at(const Point& p) const
{
    return mCells[mWidths[p.second] + p.first];
}

}
