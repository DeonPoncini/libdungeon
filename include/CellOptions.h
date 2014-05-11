#ifndef DUNGEON_CELLOPTIONS_H
#define DUNGEON_CELLOPTIONS_H

namespace dungeon
{

//! Cell Options
/*!
 * Options for controlling the parameters of dungeon generation
 */
class CellOptions
{
public:
    CellOptions();

    // setup
    CellOptions& size(unsigned width, unsigned height);
    CellOptions& iterations(unsigned iterations);
    CellOptions& initialLifeChance(float chance);
    CellOptions& edgesAlive(bool alive);
    CellOptions& deathLimit(unsigned limit);
    CellOptions& rebirthLimit(unsigned limit);

    inline unsigned width() const { return mWidth; }
    inline unsigned height() const { return mHeight; }
    inline unsigned iterations() const { return mIterations; }
    inline float initialLifeChance() const { return mInitialLifeChance; }
    inline bool edgesAlive() const { return mEdgesAlive; }
    inline unsigned deathLimit() const { return mDeathLimit; }
    inline unsigned rebirthLimit() const { return mRebirthLimit; }

private:
    unsigned mWidth;
    unsigned mHeight;
    unsigned mIterations;

    float mInitialLifeChance;
    bool  mEdgesAlive;

    unsigned mDeathLimit;
    unsigned mRebirthLimit;
};

}

#endif
