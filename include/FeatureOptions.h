#ifndef DUNGEON_FEATUREOPTIONS_H
#define DUNGEON_FEATUREOPTIONS_H

#include <functional>
#include <vector>

namespace dungeon
{

class Feature;

typedef std::function<Feature(int,int)> FeatureFunction;

//! Dungeon Options
/*!
 * Options for controlling the parameters of dungeon generation
 */
class FeatureOptions
{
public:
    FeatureOptions();

    // setup
    FeatureOptions& addFeature(FeatureFunction function, double weight = 1.0);

    FeatureOptions& size(unsigned width, unsigned height);

    FeatureOptions& minWidth(int width);
    FeatureOptions& maxWidth(int width);
    FeatureOptions& minHeight(int height);
    FeatureOptions& maxHeight(int height);

    FeatureOptions& iterations(unsigned iterations);

    Feature createRandom() const;

    inline unsigned width() const { return mWidth; }
    inline unsigned height() const { return mHeight; }
    inline unsigned iterations() const { return mIterations; }

private:
    std::vector<FeatureFunction> mFeatures;
    std::vector<double> mIntervals;
    std::vector<double> mWeights;

    unsigned mWidth;
    unsigned mHeight;

    int mMinW;
    int mMaxW;
    int mMinH;
    int mMaxH;

    unsigned mIterations;
};

}

#endif
