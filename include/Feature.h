#ifndef DUNGEON_FEATURE_H
#define DUNGEON_FEATURE_H

#include "Types.h"
#include "Cell.h"

#include <vector>

namespace dungeon
{

class Feature
{
public:
    explicit Feature(EdgeList edges);

    inline int height() const { return mEdges.size(); }
    inline int offset(int row) const { return mEdges[row].first; }
    inline int width(int row) const { return mEdges[row].second; }

    Cell at(const Point& p) const;

private:
    EdgeList mEdges;
    std::vector<Cell> mCells;
    std::vector<int> mWidths;

};

}

#endif
