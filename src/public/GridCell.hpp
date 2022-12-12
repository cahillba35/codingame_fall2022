#pragma once

#include "Vec2.hpp"

struct GridCellProperties
{
    // The first 4 variables describe properties for this cell.
    int scrapAmount;        // the number of times this tile can be recycled before becoming Grass.
    int owner;              // 1 = me, 0 = foe, -1 = neutral
    int units;              // the number of units on this cell. These units belong to the owner of the cell.
    int recycler;           // 1 if there is a recycler on this cell. This recycler belongs to the owner of the cell. 0 if there is no recycler on this cell.

    // The next 3 variables are helper values.
    int canBuild;           // 1 if you are allowed to BUILD a recycler on this tile this turn. 0 otherwise.
    int canSpawn;           // 1 if you are allowed to SPAWN units on this tile this turn. 0 otherwise.
    int inRangeOfRecycler;  // 1 if this tile's scrapAmount will be decreased at the end of the turn by a nearby recycler. 0 otherwise.
};

class GridCell
{
public:
    GridCell();
    ~GridCell();

    void Init(Vec2 pos);
    void Update(GridCellProperties properties);

private:
    Vec2 m_pos;
    GridCellProperties m_properties;
};