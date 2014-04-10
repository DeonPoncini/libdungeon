#ifndef DUNGEON_DUNGEONOPTIONS_H
#define DUNGEON_DUNGEONOPTIONS_H

#include <functional>
#include <vector>

namespace dungeon
{

class Feature;
class TileMap;

typedef std::function<Feature(int,int)> FeatureFunction;

class DungeonOptions
{
public:
    DungeonOptions();

    // setup
    DungeonOptions& addFeature(FeatureFunction function);

    DungeonOptions& setSize(unsigned width, unsigned height);

    DungeonOptions& setMinWidth(int width);
    DungeonOptions& setMaxWidth(int width);
    DungeonOptions& setMinHeight(int height);
    DungeonOptions& setMaxHeight(int height);

    Feature createRandom() const;

private:
    friend TileMap generate(const DungeonOptions& options);

    std::vector<FeatureFunction> mFeatures;

    unsigned mWidth;
    unsigned mHeight;

    int mMinW;
    int mMaxW;
    int mMinH;
    int mMaxH;
};

}

#endif
