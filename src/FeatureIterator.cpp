#include "FeatureIterator.h"

namespace dungeon
{


ForwardIterator::ForwardIterator(int height) :
    mHeight(height),
    mCurrent(0)
{
}

int ForwardIterator::begin() const
{
    mCurrent = 0;
    return mCurrent;
}

int ForwardIterator::next()
{
    ++mCurrent;
    return mCurrent;
}

int ForwardIterator::end() const
{
    return mHeight;
}

BackwardIterator::BackwardIterator(int height) :
    mHeight(height),
    mCurrent(0)
{
}

int BackwardIterator::begin() const
{
    mCurrent = mHeight - 1;
    return mCurrent;
}

int BackwardIterator::next()
{
    --mCurrent;
    return mCurrent;
}

int BackwardIterator::end() const
{
    return -1;
}


}
