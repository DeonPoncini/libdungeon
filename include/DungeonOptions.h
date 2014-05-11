#ifndef DUNGEON_DUNGEONOPTIONS_H
#define DUNGEON_DUNGEONOPTIONS_H

#include <functional>
#include <vector>

namespace dungeon
{

class Feature;
class TileMap;

typedef std::function<Feature(int,int)> FeatureFunction;

//! Dungeon Options
/*!
 * Options for controlling the parameters of dungeon generation
 */
class DungeonOptions
{
public:
    DungeonOptions();

    // setup
    DungeonOptions& addFeature(FeatureFunction function, double weight = 1.0);

    DungeonOptions& size(unsigned width, unsigned height);

    DungeonOptions& minWidth(int width);
    DungeonOptions& maxWidth(int width);
    DungeonOptions& minHeight(int height);
    DungeonOptions& maxHeight(int height);

    DungeonOptions& iterations(unsigned iterations);

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
