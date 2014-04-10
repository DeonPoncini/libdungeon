#include "FeatureIterator.h"
#include "Random.h"

#include <functional>

namespace dungeon
{

////////////////////////////////////////////////////////////////////////////////
// ADJUSTERS
////////////////////////////////////////////////////////////////////////////////

AForward::AForward(const Feature& feature) :
    mStart(randomRange(0,feature.height() - 1)),
    mOffset(feature.offset(mStart))
{
}

AMirror::AMirror(const Feature& feature) :
    mStart(randomRange(0,feature.height() - 1)),
    mOffset(feature.offset(feature.height() - 1 - mStart))
{
}

ATranspose::ATranspose(const Feature& feature) :
    mStart(randomRange(0,feature.width(0) - 1)),
    mOffset(-mStart - feature.offset(0))
{
}

AMirrorTranspose::AMirrorTranspose(const Feature& feature) :
    mStart(randomRange(0,feature.width(feature.height() - 1) - 1)),
    mOffset(-mStart - feature.offset(feature.height() - 1))
{
}

////////////////////////////////////////////////////////////////////////////////
// ITERATORS
////////////////////////////////////////////////////////////////////////////////
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

}
