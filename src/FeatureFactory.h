#ifndef DUNGEON_FEATUREFACTORY_H
#define DUNGEON_FEATUREFACTORY_H

#include <functional>
#include <string>
#include <unordered_map>

namespace dungeon
{

class Feature;

typedef std::function<Feature(int,int)> FeatureFunction;

class FeatureFactory
{
public:
    void addFeature(std::string name, FeatureFunction function);
    Feature create(const std::string& name, int width, int height) const;
    Feature createRandom(int minW, int maxW, int minH, int maxH) const;

private:
    std::unordered_map<std::string,FeatureFunction> mFeatures;
};

}

#endif
