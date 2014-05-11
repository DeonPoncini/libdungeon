#ifndef DUNGEON_UTILITY_H
#define DUNGEON_UTILITY_H

namespace dungeon
{

template <typename T, typename FI>
bool insert(T& tileMap, FI iterator);

template <typename T, typename FI>
void forceInsert(T& tileMap, FI iterator);

template <typename T, typename FI>
bool clear(T& tileMap, FI iterator);

template <typename T, typename FI>
bool insert(T& tileMap, FI iterator)
{
    if (!clear(tileMap, iterator))
    {
        return false;
    }

    forceInsert(tileMap, iterator);
    return true;
}

template <typename T, typename FI>
void forceInsert(T& tileMap, FI iterator)
{
    for (auto&& row : iterator)
    {
        for (auto&& point : row)
        {
            tileMap.set(iterator.transform(point), (*iterator)->at(point));
        }
    }
}

template <typename T, typename FI>
bool clear(T& tileMap, FI iterator)
{
    for (auto&& row : iterator)
    {
        for (auto&& point : row)
        {
            if (!tileMap.clear(iterator.transform(point)))
            {
                return false;
            }
        }
    }
    return true;
}


}

#endif
