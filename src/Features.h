#ifndef DUNGEON_FEATURES_H
#define DUNGEON_FEATURES_H

namespace dungeon
{

class Feature;

Feature corridor(int length, int unused = 0);
Feature diamond(int rows, int unused = 0);
Feature door(int unused = 0, int unused_ = 0);
Feature octogon(int side, int unused = 0);
Feature rectangle(int width, int height);
Feature trapezium(int top, int height);
Feature triangle(int rows, int unused = 0);

}

#endif
