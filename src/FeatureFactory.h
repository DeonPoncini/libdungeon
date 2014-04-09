#ifndef DUNGEON_FEATUREFACTORY_H
#define DUNGEON_FEATUREFACTORY_H

#include <functional>
#include <vector>

namespace dungeon
{

class Feature;

typedef std::function<Feature(int,int)> FeatureFunction;

class FeatureFactory
{
public:
    void addFeature(FeatureFunction function);
    Feature createRandom(int minW, int maxW, int minH, int maxH) const;

private:
    std::vector<FeatureFunction> mFeatures;
};

}

#endif
