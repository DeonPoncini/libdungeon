#include "FeatureIterator.h"
#include "Random.h"

#include <functional>

namespace dungeon
{

////////////////////////////////////////////////////////////////////////////////
// ADJSUTERS
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

AForward::AForward(const Feature& feature) :
    mStart(randomRange(0,feature.height() - 1)),
    mOffset(feature.offset(mStart))
{
}

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

AMirror::AMirror(const Feature& feature) :
    mStart(randomRange(0,feature.height() - 1)),
    mOffset(feature.offset(feature.height() - 1 - mStart))
{
}

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

ATranspose::ATranspose(const Feature& feature) :
    mStart(randomRange(0,feature.width(0) - 1)),
    mOffset(-mStart - feature.offset(0))
{
}

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

AMirrorTranspose::AMirrorTranspose(const Feature& feature) :
    mStart(randomRange(0,feature.width(feature.height() - 1) - 1)),
    mOffset(-mStart - feature.offset(feature.height() - 1))
{
}


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

IForward::IForward(int height) :
    mHeight(height),
    mCurrent(0)
{
}

int IForward::begin() const
{
    mCurrent = 0;
    return mCurrent;
}

int IForward::next()
{
    ++mCurrent;
    return mCurrent;
}

int IForward::end() const
{
    return mHeight;
}

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

IBackward::IBackward(int height) :
    mHeight(height),
    mCurrent(0)
{
}

int IBackward::begin() const
{
    mCurrent = mHeight - 1;
    return mCurrent;
}

int IBackward::next()
{
    --mCurrent;
    return mCurrent;
}

int IBackward::end() const
{
    return -1;
}

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

template <typename A>
YForwardShift<A>::YForwardShift(const Feature& feature,
        const Point& location, const A& adjuster) :
    mValue(location.second - adjuster.start())
{
}

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

template <typename A>
YTranspose<A>::YTranspose(const Feature& feature, const Point&
        location, const A& adjuster) :
    mValue(location.first)
{
}

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
YMirrorTranspose<A>::YMirrorTranspose(const Feature& feature,
        const Point& location, const A& adjuster) :
    mValue(location.first - (feature.height() - 1))
{
}

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
YMirror<A>::YMirror(const Feature& feature,
        const Point& location, const A& adjuster) :
    mValue(location.second - (feature.height() - 1))
{
}

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
YTransposeShift<A>::YTransposeShift(const Feature& feature,
        const Point& location, const A& adjuster) :
    mValue(location.first - adjuster.start())
{
}

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
YMirrorTransposeShift<A>::YMirrorTransposeShift(const Feature& feature,
        const Point& location, const A& adjuster) :
    mValue(location.first - (feature.height() - 1) + adjuster.start())
{
}

template <typename A>
class YForward
{
public:
    YForward(const Feature& feature, const Point& location, const A& adjuster);

    inline int operator()() const { return mValue; }

private:
    int mValue;
};

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
class XForward
{
public:
    XForward(const Feature& feature, const Point& location, const A& adjuster);

    inline int operator()(int y) const { return mF(y); }

private:
    std::function<int(int)> mF;
};

template <typename A>
XForward<A>::XForward(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([&](int y){
            return location.first + feature.offset(y) - adjuster.offset();})
{
}

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
XMirror<A>::XMirror(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([&](int y){
            return location.first + feature.offset(y) + adjuster.offset();})
{
}

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
XMirrorTranspose<A>::XMirrorTranspose(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([&](int y){
            return location.second + feature.offset(y) + adjuster.offset();})
{
}

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
XTranspose<A>::XTranspose(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([&](int y){
            return location.second + feature.offset(y) - adjuster.offset();})
{
}

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
XForwardShift<A>::XForwardShift(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([&](int y){
            return location.first + feature.offset(y) - adjuster.offset()
            - (feature.width(adjuster.start()) - 1);})
{
}

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
XTransposeShift<A>::XTransposeShift(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([&](int y){
            return location.second -
            (feature.width(feature.height() - 1 - adjuster.start()) - 1)
            + feature.offset(y) - adjuster.offset();})
{
}

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

template <typename A>
XMirrorShift<A>::XMirrorShift(const Feature& feature,
        const Point& location, const A& adjuster) :
    mF([&](int y){
            return location.first + feature.offset(y) - adjuster.offset()
            - (feature.width(feature.height() - 1 - adjuster.start()) - 1);})
{
}

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
OForward<X,Y>::OForward(const Feature& feature, X x, Y y) :
    mLocation([&](int _x, int _y)
            { return Point{x(_y) + _x, y() + _y}; })
{
}

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
OTranspose<X,Y>::OTranspose(const Feature& feature, X x, Y y) :
    mLocation([&](int _x, int _y)
            { return Point{y() + _y, x(_y) + _x}; })
{
}

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
OMirror<X,Y>::OMirror(const Feature& feature, X x, Y y) :
    mLocation([&](int _x, int _y)
            { return Point{x(_y) + _x, y() + feature.height() - 1 - _y}; })
{
}

template <typename X, typename Y>
class OMirrorTranspose
{
public:
    OMirrorTranspose(const Feature& feature, X x, Y y);

    inline Point operator()(int x, int y) const { return mLocation(x,y); }

private:
    std::function<Point(int, int)> mLocation;
};

template <typename X, typename Y>
OMirrorTranspose<X,Y>::OMirrorTranspose(const Feature& feature, X x, Y y) :
    mLocation([&](int _x, int _y)
            { return Point{y() + feature.height() - 1 - _y, x(_y) + _x}; })
{
}

}

