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
 * A: Adjuster that calculates random offsets for the shapes
 * I: Iterator that counts either forwards or backwards over
 *    the rows of the feature
 * Y: Return the world space Y coordinate for the the position of the first
 *    row of the feature
 * X: Return the world space X coordinate for the start of each row in the
 *    feature
 * O: Orientation computes the rotation of the shape
 *
 */
template <typename A,
         typename I,
         template<typename> class Y,
         template<typename> class X,
         template<typename, typename> class O>
class FeatureIterator
{
public:
    FeatureIterator(const Feature& feature, const Point& location);

    int begin() const;
    int next();
    int end() const;

    Point operator()(int x, int y) const;

private:
    int startY() const;
    int startX(int y) const;

    A adjuster;
    I iterator;
    Y<A> y;
    X<A> x;
    O<X<A>,Y<A>> orientation;
};

template <typename A,
         typename I,
         template<typename> class Y,
         template<typename> class X,
         template<typename, typename> class O>
FeatureIterator<A,I,Y,X,O>::FeatureIterator(
        const Feature& feature, const Point& location) :
        adjuster(feature),
        iterator(feature.height()),
        y(feature,location,adjuster),
        x(feature,location,adjuster),
        orientation(feature,x,y)
{
}

template <typename A,
         typename I,
         template<typename> class Y,
         template<typename> class X,
         template<typename, typename> class O>
int FeatureIterator<A,I,Y,X,O>::begin() const
{
    return iterator.begin();
}

template <typename A,
         typename I,
         template<typename> class Y,
         template<typename> class X,
         template<typename, typename> class O>
int FeatureIterator<A,I,Y,X,O>::next()
{
    return iterator.next();
}

template <typename A,
         typename I,
         template<typename> class Y,
         template<typename> class X,
         template<typename, typename> class O>
int FeatureIterator<A,I,Y,X,O>::end() const
{
    return iterator.end();
}

template <typename A,
         typename I,
         template<typename> class Y,
         template<typename> class X,
         template<typename, typename> class O>
Point FeatureIterator<A,I,Y,X,O>::operator()(int x, int y) const
{
    return orientation(x,y);
}

template <typename A,
         typename I,
         template<typename> class Y,
         template<typename> class X,
         template<typename, typename> class O>
int FeatureIterator<A,I,Y,X,O>::startY() const
{
    return Y<A>();
}

template <typename A,
         typename I,
         template<typename> class Y,
         template<typename> class X,
         template<typename, typename> class O>
int FeatureIterator<A,I,Y,X,O>::startX(int y) const
{
    return X<A>(y);
}

// forward declarations

// adjusters
class AForward;
class AMirror;
class ATranspose;
class AMirrorTranspose;

// iterators
class IForward;
class IBackward;

// Y transforms
template <typename A> class YForwardShift;
template <typename A> class YTranspose;
template <typename A> class YMirrorTranspose;
template <typename A> class YMirror;
template <typename A> class YTransposeShift;
template <typename A> class YMirrorTransposeShift;
template <typename A> class YForward;

// X transforms
template <typename A> class XForward;
template <typename A> class XMirror;
template <typename A> class XMirrorTranspose;
template <typename A> class XTranspose;
template <typename A> class XForwardShift;
template <typename A> class XTransposeShift;
template <typename A> class XMirrorShift;

// orientations
template <typename X, typename Y> class OForward;
template <typename X, typename Y> class OTranspose;
template <typename X, typename Y> class OMirror;
template <typename X, typename Y> class OMirrorTranspose;

// typedefs
/*
 * Starting from the selected location with a given feature there
 * are 16 possible ways we can iterate over the shape in world space
 * to try and make it fit. We can orient the shape in four ways:
 * F - Forward - with rows running left to right top to bottom
 * T - Transpose - the shape turned clockwise 90 degrees
 * M - Mirror - the shape turned clockwise 180 degrees
 * Z - Transpose Mirror - the shape turned clockwise 270 degrees
 *
 * Then we can put this shape in four places around our location
 * R - To the right
 * L - To the left
 * A - Above the point
 * B - Below the point
 *
 * We express our iterators as <place><rotation> so RF is to the right
 * and forward, the normal way we would think of laying out a feature
 */

// to the right
typedef FeatureIterator<
        AForward, IForward, YForwardShift, XForward, OForward>      RF;
typedef FeatureIterator<
        AMirror, IBackward, YForwardShift, XForward, OMirror>       RM;
typedef FeatureIterator<
        AMirrorTranspose, IBackward, YTranspose,
        XMirrorTranspose, OMirrorTranspose>                         RT;
typedef FeatureIterator<
        ATranspose, IForward, YTranspose,
        XMirrorTranspose, OTranspose>                               RZ;

// to the left
typedef FeatureIterator<
        AForward, IForward, YForwardShift, XForwardShift, OForward> LF;
typedef FeatureIterator<
        AMirror, IBackward, YForwardShift, XMirrorShift, OMirror>   LM;
typedef FeatureIterator<
        ATranspose, IBackward, YMirrorTranspose,
        XMirrorTranspose, OMirrorTranspose>                         LT;
typedef FeatureIterator<
        AMirrorTranspose, IForward, YMirrorTranspose,
        XMirrorTranspose, OTranspose>                               LZ;

// above
typedef FeatureIterator<
        AMirrorTranspose, IForward, YMirror, XMirror, OForward>     AF;
typedef FeatureIterator<
        ATranspose, IBackward, YMirror, XMirror, OMirror>           AM;
typedef FeatureIterator<
        AMirror, IBackward, YTransposeShift,
        XTransposeShift, OMirrorTranspose>                          AT;
typedef FeatureIterator<
        AMirror, IForward, YMirrorTransposeShift,
        XTransposeShift, OTranspose>                                AZ;

// below
typedef FeatureIterator<
        ATranspose, IForward, YForward, XMirror, OForward>          BF;
typedef FeatureIterator<
        AMirrorTranspose, IBackward, YForward, XMirror, OMirror>    BM;
typedef FeatureIterator<
        AMirror, IBackward, YTransposeShift,
        XTranspose, OMirrorTranspose>                               BT;
typedef FeatureIterator<
        AMirror, IForward, YMirrorTransposeShift,
        XTranspose, OTranspose>                                     BZ;

}

#endif
