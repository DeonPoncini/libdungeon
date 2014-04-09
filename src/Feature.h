#ifndef DUNGEON_FEATURE_H
#define DUNGEON_FEATURE_H

#include <vector>
#include <utility>

namespace dungeon
{

class Feature
{
public:
    typedef std::pair<int,int> Edge;
    typedef std::vector<std::pair<int,int>> EdgeList;

    explicit Feature(EdgeList edges);

    inline int height() const { return mEdges.size(); }
    inline int offset(int row) const { return mEdges[row].first; }
    inline int width(int row) const { return mEdges[row].second; }

private:
    EdgeList mEdges;

};

}

#endif
