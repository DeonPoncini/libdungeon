#ifndef DUNGEON_FEATURE_ITERATOR_H
#define DUNGEON_FEATURE_ITERATOR_H

#include "Feature.h"

#include <functional>

namespace dungeon
{

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


// classes

////////////////////////////////////////////////////////////////////////////////
// ADJUSTERS
////////////////////////////////////////////////////////////////////////////////
/*
 * Set the start and offset for 0 degree oriented features
 */

class AForward
{
public:
    AForward(const Feature& feature);

    inline int start() const { return mStart; }
    inline int offset() const { return mOffset; }

private:
    int mStart;
    int mOffset;
};

/*
 * Set the start and offset for 180 degree oriented features
 */
class AMirror
{
public:
    AMirror(const Feature& feature);

    inline int start() const { return mStart; }
    inline int offset() const { return mOffset; }

private:
    int mStart;
    int mOffset;
};

/*
 * Set the start and offset for 90 degree oriented features
 */
class ATranspose
{
public:
    ATranspose(const Feature& feature);

    inline int start() const { return mStart; }
    inline int offset() const { return mOffset; }

private:
    int mStart;
    int mOffset;
};

/*
 * Set the start and offset for 270 degree oriented features
 */
class AMirrorTranspose
{
public:
    AMirrorTranspose(const Feature& feature);

    inline int start() const { return mStart; }
    inline int offset() const { return mOffset; }

private:
    int mStart;
    int mOffset;
};

////////////////////////////////////////////////////////////////////////////////
// ITERATORS
////////////////////////////////////////////////////////////////////////////////
/*
 * Iterate over feature rows from the top to the bottom
 */
class IForward
{
public:
    IForward(int height);

    int begin() const;
    int next();
    int end() const;

private:
    const int mHeight;
    mutable int mCurrent;
};

/*
 * Iterate over feature rows from the bottom to the top
 */
class IBackward
{
public:
    IBackward(int height);

    int begin() const;
    int next();
    int end() const;

private:
    const int mHeight;
    mutable int mCurrent;
};

////////////////////////////////////////////////////////////////////////////////
// Y TRANSFORMS
////////////////////////////////////////////////////////////////////////////////
/*
 * Y coordinate transform for forward oriented features
 */
template <typename A>
class YForwardShift
{
public:
    YForwardShift(const Feature& feature,
            const Point& location, const A& adjuster);

    inline int operator()() const { return mValue; }

private:
    int mValue;
};

/*
 * Y coordinate transform for transposed forward oriented feature
 */
template <typename A>
class YTranspose
{
public:
    YTranspose(const Feature& feature,
            const Point& location, const A& adjuster);

    inline int operator()() const { return mValue; }

private:
    int mValue;
};

/*
 * Y coordinate transform for transposed backward oriented features
 */
template <typename A>
class YMirrorTranspose
{
public:
    YMirrorTranspose(const Feature& feature,
            const Point& location, const A& adjuster);

    inline int operator()() const { return mValue; }

private:
    int mValue;
};

template <typename A>
class YMirror
{
public:
    YMirror(const Feature& feature, const Point& location, const A& adjuster);

    inline int operator()() const { return mValue; }

private:
    int mValue;
};

template <typename A>
class YTransposeShift
{
public:
    YTransposeShift(const Feature& feature,
            const Point& location, const A& adjuster);

    inline int operator()() const { return mValue; }

private:
    int mValue;
};

template <typename A>
class YMirrorTransposeShift
{
public:
    YMirrorTransposeShift(const Feature& feature,
            const Point& location, const A& adjuster);

    inline int operator()() const { return mValue; }

private:
    int mValue;
};

template <typename A>
class YForward
{
public:
    YForward(const Feature& feature, const Point& location, const A& adjuster);

    inline int operator()() const { return mValue; }

private:
    int mValue;
};

////////////////////////////////////////////////////////////////////////////////
// X TRANSFORMS
////////////////////////////////////////////////////////////////////////////////

template <typename A>
class XForward
{
public:
    XForward(const Feature& feature, const Point& location, const A& adjuster);

    inline int operator()(int y) const { return mF(y); }

private:
    std::function<int(int)> mF;
};

template <typename A>
class XMirror
{
public:
    XMirror(const Feature& feature, const Point& location, const A& adjuster);

    inline int operator()(int y) const { return mF(y); }

private:
    std::function<int(int)> mF;
};

template <typename A>
class XMirrorTranspose
{
public:
    XMirrorTranspose(const Feature& feature,
            const Point& location, const A& adjuster);

    inline int operator()(int y) const { return mF(y); }

private:
    std::function<int(int)> mF;
};

template <typename A>
class XTranspose
{
public:
    XTranspose(const Feature& feature,
            const Point& location, const A& adjuster);

    inline int operator()(int y) const { return mF(y); }

private:
    std::function<int(int)> mF;
};

template <typename A>
class XForwardShift
{
public:
    XForwardShift(const Feature& feature,
            const Point& location, const A& adjuster);

    inline int operator()(int y) const { return mF(y); }

private:
    std::function<int(int)> mF;
};

template <typename A>
class XTransposeShift
{
public:
    XTransposeShift(const Feature& feature,
            const Point& location, const A& adjuster);

    inline int operator()(int y) const { return mF(y); }

private:
    std::function<int(int)> mF;
};

template <typename A>
class XMirrorShift
{
public:
    XMirrorShift(const Feature& feature,
            const Point& location, const A& adjuster);

    inline int operator()(int y) const { return mF(y); }

private:
    std::function<int(int)> mF;
};

////////////////////////////////////////////////////////////////////////////////
// Orientations
////////////////////////////////////////////////////////////////////////////////
template <typename X, typename Y>
class OForward
{
public:
    OForward(const Feature& feature, X x, Y y);

    inline Point operator()(int x, int y) const { return mLocation(x,y); }

private:
    std::function<Point(int, int)> mLocation;
};

template <typename X, typename Y>
class OTranspose
{
public:
    OTranspose(const Feature& feature, X x, Y y);

    inline Point operator()(int x, int y) const { return mLocation(x,y); }

private:
    std::function<Point(int, int)> mLocation;
};

template <typename X, typename Y>
class OMirror
{
public:
    OMirror(const Feature& feature, X x, Y y);

    inline Point operator()(int x, int y) const { return mLocation(x,y); }

private:
    std::function<Point(int, int)> mLocation;
};

template <typename X, typename Y>
class OMirrorTranspose
{
public:
    OMirrorTranspose(const Feature& feature, X x, Y y);

    inline Point operator()(int x, int y) const { return mLocation(x,y); }

private:
    std::function<Point(int, int)> mLocation;
};

// implementations

////////////////////////////////////////////////////////////////////////////////
// Y TRANSFORMS
////////////////////////////////////////////////////////////////////////////////
template <typename A>
YForwardShift<A>::YForwardShift(const Feature& feature,
        const Point& location, const A& adjuster) :
    mValue(location.second - adjuster.start())
{
}

template <typename A>
YTranspose<A>::YTranspose(const Feature& feature, const Point&
        location, const A& adjuster) :
    mValue(location.first)
{
}

template <typename A>
YMirrorTranspose<A>::YMirrorTranspose(const Feature& feature,
        const Point& location, const A& adjuster) :
    mValue(location.first - (feature.height() - 1))
{
}

template <typename A>
YMirror<A>::YMirror(const Feature& feature,
        const Point& location, const A& adjuster) :
    mValue(location.second - (feature.height() - 1))
{
}

template <typename A>
YTransposeShift<A>::YTransposeShift(const Feature& feature,
        const Point& location, const A& adjuster) :
    mValue(location.first - adjuster.start())
{
}

template <typename A>
YMirrorTransposeShift<A>::YMirrorTransposeShift(const Feature& feature,
        const Point& location, const A& adjuster) :
    mValue(location.first - (feature.height() - 1) + adjuster.start())
{
}

template <typename A>
YForward<A>::YForward(const Feature& feature,
        const Point& location, const A& adjuster) :
    mValue(location.second)
{
}

////////////////////////////////////////////////////////////////////////////////
// X TRANSFORMS
////////////////////////////////////////////////////////////////////////////////
template <typename A>
XForward<A>::XForward(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([=](int y){
            return location.first + feature.offset(y) - adjuster.offset();})
{
}

template <typename A>
XMirror<A>::XMirror(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([=](int y){
            return location.first + feature.offset(y) + adjuster.offset();})
{
}

template <typename A>
XMirrorTranspose<A>::XMirrorTranspose(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([=](int y){
            return location.second + feature.offset(y) + adjuster.offset();})
{
}

template <typename A>
XTranspose<A>::XTranspose(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([=](int y){
            return location.second + feature.offset(y) - adjuster.offset();})
{
}

template <typename A>
XForwardShift<A>::XForwardShift(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([=](int y){
            return location.first + feature.offset(y) - adjuster.offset()
            - (feature.width(adjuster.start()) - 1);})
{
}

template <typename A>
XTransposeShift<A>::XTransposeShift(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([=](int y){
            return location.second -
            (feature.width(feature.height() - 1 - adjuster.start()) - 1)
            + feature.offset(y) - adjuster.offset();})
{
}

template <typename A>
XMirrorShift<A>::XMirrorShift(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([=](int y){
            return location.first + feature.offset(y) - adjuster.offset()
            - (feature.width(feature.height() - 1 - adjuster.start()) - 1);})
{
}

////////////////////////////////////////////////////////////////////////////////
// Orientations
////////////////////////////////////////////////////////////////////////////////
template <typename X, typename Y>
OForward<X,Y>::OForward(const Feature& feature, X x, Y y) :
    mLocation([=](int _x, int _y)
            { return Point{x(_y) + _x, y() + _y}; })
{
}

template <typename X, typename Y>
OTranspose<X,Y>::OTranspose(const Feature& feature, X x, Y y) :
    mLocation([=](int _x, int _y)
            { return Point{y() + _y, x(_y) + _x}; })
{
}

template <typename X, typename Y>
OMirror<X,Y>::OMirror(const Feature& feature, X x, Y y) :
    mLocation([=](int _x, int _y)
            { return Point{x(_y) + _x, y() + feature.height() - 1 - _y}; })
{
}

template <typename X, typename Y>
OMirrorTranspose<X,Y>::OMirrorTranspose(const Feature& feature, X x, Y y) :
    mLocation([=](int _x, int _y)
            { return Point{y() + feature.height() - 1 - _y, x(_y) + _x}; })
{
}

}

#endif
