#ifndef DUNGEON_CELL_H
#define DUNGEON_CELL_H

namespace dungeon
{

class Cell
{
public:
    Cell();
    explicit Cell(bool valid);

    inline bool valid() const { return static_cast<bool>(mValid); }
    void valid(bool valid) { mValid = static_cast<unsigned char>(valid); }

private:
    unsigned char mValid : 1;
};

}

#endif
