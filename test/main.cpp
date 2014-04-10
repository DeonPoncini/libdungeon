#include <iostream>

#include "FeatureIterator.h"
#include "Features.h"
#include "TileMap.h"
#include "Generator.h"
#include "DungeonOptions.h"

void print(const dungeon::TileMap& tileMap, const dungeon::Point& p)
{
    // print the map out
    auto width = tileMap.width();
    auto height = tileMap.height();
    for (auto y = 0U; y < height; y++)
    {
        for (auto x = 0U; x < width; x++)
        {
            if (x == static_cast<unsigned>(p.first) &&
                y == static_cast<unsigned>(p.second))
            {
                std::cout << "*";
                continue;
            }
            if (tileMap.at({x,y}) == nullptr)
            {
                std::cout << ' ';
            }
            else
            {
                std::cout << '#';
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    dungeon::DungeonOptions options;
//    options.addFeature(dungeon::corridor);
 //   options.addFeature(dungeon::diamond);
 //   options.addFeature(dungeon::octogon);
    options.addFeature(dungeon::rectangle);
//    options.addFeature(dungeon::trapezium);

    // generate the dungeon
    auto tileMap = dungeon::generate(options);
    print(tileMap,{0,0});


#if 0
    auto width = 20;
    auto height = 20;
    dungeon::Point p{10,10};
    auto triangle = dungeon::triangle(4);

    std::cout << "Testing Right Forward" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::RF rf(triangle,p);
        tileMap.insert(&triangle,rf);
        print(tileMap,p);
    }

    std::cout << "Testing Right Mirror" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::RM rm(triangle,p);
        tileMap.insert(&triangle,rm);
        print(tileMap,p);
    }

    std::cout << "Testing Right Transpose" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::RT rt(triangle,p);
        tileMap.insert(&triangle,rt);
        print(tileMap,p);
    }

    std::cout << "Testing Right Tranpose Mirror" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::RZ rz(triangle,p);
        tileMap.insert(&triangle,rz);
        print(tileMap,p);
    }

    std::cout << "Testing Left Forward" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::LF lf(triangle,p);
        tileMap.insert(&triangle,lf);
        print(tileMap,p);
    }

    std::cout << "Testing Left Mirror" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::LM lm(triangle,p);
        tileMap.insert(&triangle,lm);
        print(tileMap,p);
    }

    std::cout << "Testing Left Transpose" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::LT lt(triangle,p);
        tileMap.insert(&triangle,lt);
        print(tileMap,p);
    }

    std::cout << "Testing Left Transpose Mirror" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::LZ lz(triangle,p);
        tileMap.insert(&triangle,lz);
        print(tileMap,p);
    }

    std::cout << "Testing Above Forward" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::AF af(triangle,p);
        tileMap.insert(&triangle,af);
        print(tileMap,p);
    }

    std::cout << "Testing Above Mirror" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::AM am(triangle,p);
        tileMap.insert(&triangle,am);
        print(tileMap,p);
    }

    std::cout << "Testing Above Transpose" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::AT at(triangle,p);
        tileMap.insert(&triangle,at);
        print(tileMap,p);
    }

    std::cout << "Testing Above Mirror Transpose" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::AZ az(triangle,p);
        tileMap.insert(&triangle,az);
        print(tileMap,p);
    }

    std::cout << "Testing Below Forward" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::BF bf(triangle,p);
        tileMap.insert(&triangle,bf);
        print(tileMap,p);
    }

    std::cout << "Testing Below Mirror" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::BM bm(triangle,p);
        tileMap.insert(&triangle,bm);
        print(tileMap,p);
    }

    std::cout << "Testing Below Transpose" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::BT bt(triangle,p);
        tileMap.insert(&triangle,bt);
        print(tileMap,p);
    }

    std::cout << "Testing Below Mirror Transpose" << std::endl;
    {
        dungeon::TileMap tileMap(width,height);
        dungeon::BZ bz(triangle,p);
        tileMap.insert(&triangle,bz);
        print(tileMap,p);
    }
#endif

    return 0;
}
