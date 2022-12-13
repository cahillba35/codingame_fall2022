#pragma once

#include "Vec2.hpp"

#include <vector>

struct TileProperties
{
    // The first 4 variables describe properties for this tile.
    int scrapAmount;        // the number of times this tile can be recycled before becoming Grass.
    int owner;              // 1 = me, 0 = foe, -1 = neutral
    int units;              // the number of units on this tile. These units belong to the owner of the tile.
    int recycler;           // 1 if there is a recycler on this tile. This recycler belongs to the owner of the tile. 0 if there is no recycler on this tile.

    // The next 3 variables are helper values.
    int canBuild;           // 1 if you are allowed to BUILD a recycler on this tile this turn. 0 otherwise.
    int canSpawn;           // 1 if you are allowed to SPAWN units on this tile this turn. 0 otherwise.
    int inRangeOfRecycler;  // 1 if this tile's scrapAmount will be decreased at the end of the turn by a nearby recycler. 0 otherwise.
};

class Tile
{
public:
    Tile() {}
    ~Tile() {}

    void Init(Vec2 pos);
    void SetProperties(TileProperties properties);

    bool IsEmpty() const { return m_properties.owner == -1; }
    bool IsMyTile() const { return m_properties.owner == 1; }
    bool IsOppTile() const { return m_properties.owner == 0; }

    bool HasRecycler() const { return m_properties.recycler == 1; }
    bool HasUnits() const { return m_properties.units > 0; }
    int GetUnits() const { return m_properties.units; }

    bool CanBuildRecycler() const { return m_properties.canBuild == 1; }
    bool CanSpawnUnits() const { return m_properties.canSpawn == 1; }
    bool IsInRangeOfRecycler() const { return m_properties.inRangeOfRecycler == 1; }

    bool operator==(const Tile& other) const { return m_pos == other.m_pos; }

private:
    Vec2 m_pos;
    TileProperties m_properties;
};

class MapManager
{
public:
    MapManager();
    ~MapManager();

    void Init(Vec2 size);

    static MapManager& GetInstance()
    {
        static MapManager instance;
        return instance;
    }

    Vec2 GetSize() const { return m_size; }

    void UpdateTileProperties(const Vec2& pos, TileProperties properties);
    const Tile& GetTile(const Vec2& pos) const;

private:
    Vec2 m_size;

    std::vector<Tile> m_tiles;
};