#ifndef DUNGEON_FEATURE_ITERATOR_H
#define DUNGEON_FEATURE_ITERATOR_H

#include "Feature.h"

namespace dungeon
{

typedef std::pair<int,int> Point;

/**
 * A feature can be placed in the world map in 16 possible ways
 * From each location that the feature can be placed, the feature can be
 * drawn either top to bottom or bottom to top, then either left to right
 * or right to left, and finally the location could be the top left, bottom
 * left, top right or bottom right corner of the feature shape.
 *
 * Finally the shape is offset by an adjuster by a random amount to
 * select the contact edge to the location so features don't always connect
 * at their corners
 *
 *
 *
 * A: Adjuster that calculates random offsets for the shapes
 * I: Iterator that counts either forwards or backwards over
 *    the rows of the feature
 * C: Coordinate that converts feature coordinates to
 *    world tile space coordinates offset from the location
 * O: Orientation computes the rotation of the shape
 *
 */
template <typename A, typename I, typename C, typename O>
class FeatureIterator
{
public:
    FeatureIterator(const Feature& feature, const Point& location);

    int begin() const;
    int next();
    int end() const;

    Point operator()(int x, int y) const;

private:
    int startX() const;
    int startY(int x) const;

    A adjuster;
    I iterator;
    C coordinates;
    O orientation;
};

template <typename A, typename I, typename C, typename O>
FeatureIterator<A,I,C,O>::FeatureIterator(
        const Feature& feature, const Point& location) :
        adjuster(feature),
        iterator(feature.height()),
        coordinates(feature,location,adjuster),
        orientation(coordinates)
{
}

template <typename A, typename I, typename C, typename O>
int FeatureIterator<A,I,C,O>::begin() const
{
    return iterator.begin();
}

template <typename A, typename I, typename C, typename O>
int FeatureIterator<A,I,C,O>::next()
{
    return iterator.next();
}

template <typename A, typename I, typename C, typename O>
int FeatureIterator<A,I,C,O>::end() const
{
    return iterator.end();
}

template <typename A, typename I, typename C, typename O>
Point FeatureIterator<A,I,C,O>::operator()(int x, int y) const
{
    return orientation(x,y);
}

class RowAdjuster
{
public:
    RowAdjuster(const Feature& feature);

    inline int start() const { return mStart; }
    inline int offset() const { return mOffset; }

private:
    int mStart;
    int mOffset;
};


class ForwardIterator
{
public:
    ForwardIterator(int height);

    int begin() const;
    int next();
    int end() const;

private:
    const int mHeight;
    mutable int mCurrent;
};

class BackwardIterator
{
public:
    BackwardIterator(int height);

    int begin() const;
    int next();
    int end() const;

private:
    const int mHeight;
    mutable int mCurrent;
};



}


#endif
