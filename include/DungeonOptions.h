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

    DungeonOptions& setSize(unsigned width, unsigned height);

    DungeonOptions& setMinWidth(int width);
    DungeonOptions& setMaxWidth(int width);
    DungeonOptions& setMinHeight(int height);
    DungeonOptions& setMaxHeight(int height);

    DungeonOptions& setIterations(unsigned iterations);

    Feature createRandom() const;

private:
    friend TileMap generate(const DungeonOptions& options);

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
