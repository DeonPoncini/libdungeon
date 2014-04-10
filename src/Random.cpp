#include "Random.h"

#include <random>

namespace dungeon
{

int randomRange(int start, int end)
{
    static std::random_device device;
    static std::mt19937 gen(device());
    std::uniform_int_distribution<> dist(start,end);
    return dist(gen);
}

}
