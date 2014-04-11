#include "Features.h"
#include "Feature.h"

namespace dungeon
{

Feature corridor(int length, int)
{
    return Feature({{0,length}});
}

Feature diamond(int rows, int)
{
    // the offset starts at rows
    // the rows are (i+1)*2 -1 wide
    EdgeList edges;
    for (auto i = 0; i < rows / 2; i++)
    {
        edges.push_back({rows/2-i-1,(i+1)*2-1});
    }

    // bottom half of diamond
    for (auto i = rows / 2 - 1; i >= 0; i--)
    {
        edges.push_back({rows / 2 - i - 1,(i+1)*2-1});
    }
    return Feature(edges);
}

Feature door(int, int)
{
    // just a single tile
    return Feature({{0,1}});
}

Feature octogon(int side, int)
{
    // total number of rows is side * 3
    // top segment has side - 1 sections that increase by 2 each time
    // segment 2 has identitical sides offset 0 length side + 2*(side-1)
    // segment 3 has side -1 seconds, inverse of section 1

    EdgeList edges;
    side /= 3;
    if (side < 2) side = 2;

    for (auto i = 0; i < side - 1; i++)
    {
        edges.push_back({side-1-i,side+i*2});
    }

    for (auto i = 0; i < side; i++)
    {
        edges.push_back({0,side+2*(side-1)});
    }

    for (auto i = side - 2; i >= 0; i--)
    {
        edges.push_back({side-1-i,side+i*2});
    }
    return Feature(edges);
}

Feature rectangle(int width, int height)
{
    EdgeList edges;
    for (auto i = 0; i < height; i++)
    {
        edges.push_back({0,width});
    }
    return Feature(edges);
}

Feature trapezium(int top, int height)
{
    EdgeList edges;
    for (auto i = 0; i < height; i++)
    {
        edges.push_back({top-1-i,top+i*2});
    }
    return Feature(edges);
}

Feature triangle(int rows, int)
{
    EdgeList edges;
    for (auto i = 0; i < rows; i++)
    {
        edges.push_back({rows-i-1,(i+1)*2-1});
    }
    return Feature(edges);
}

}
