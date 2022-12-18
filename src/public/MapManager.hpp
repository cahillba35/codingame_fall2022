#pragma once

#include "Game.hpp"

#include "helpers.hpp"

#include <vector>
#include <string>

struct TileProperties
{
    TileProperties() {}
    TileProperties(int _x, int _y)
        : x(_x)
        , y(_y)
        , scrapAmount(0)
        , owner(-1)
        , units(0)
        , recycler(0)
        , canBuild(0)
        , canSpawn(0)
        , inRangeOfRecycler(0)
    {
    }

    int x; int y; // The position of this tile.

    // The first 4 variables describe properties for this tile.
    int scrapAmount;        // the number of times this tile can be recycled before becoming Grass.
    int owner;              // 1 = me, 0 = foe, -1 = neutral
    int units;              // the number of units on this tile. These units belong to the owner of the tile.
    int recycler;           // 1 if there is a recycler on this tile. This recycler belongs to the owner of the tile. 0 if there is no recycler on this tile.

    // The next 3 variables are helper values.
    int canBuild;           // 1 if you are allowed to BUILD a recycler on this tile this turn. 0 otherwise.
    int canSpawn;           // 1 if you are allowed to SPAWN units on this tile this turn. 0 otherwise.
    int inRangeOfRecycler;  // 1 if this tile's scrapAmount will be decreased at the end of the turn by a nearby recycler. 0 otherwise.

    std::string ToString() const
    {
        std::string s = "TileProperties: ";
        s += "x: " + std::to_string(x) + ", ";
        s += "y: " + std::to_string(y) + ", ";
        s += "scrapAmount: " + std::to_string(scrapAmount) + ", ";
        s += "owner: " + std::to_string(owner) + ", ";
        s += "units: " + std::to_string(units) + ", ";
        s += "recycler: " + std::to_string(recycler) + ", ";
        s += "canBuild: " + std::to_string(canBuild) + ", ";
        s += "canSpawn: " + std::to_string(canSpawn) + ", ";
        s += "inRangeOfRecycler: " + std::to_string(inRangeOfRecycler);
        return s;
    }

    bool operator==(const TileProperties& other) const
    {
        return x == other.x &&
            y == y &&
            scrapAmount == other.scrapAmount &&
            owner == other.owner &&
            units == other.units &&
            recycler == other.recycler &&
            canBuild == other.canBuild &&
            canSpawn == other.canSpawn &&
            inRangeOfRecycler == other.inRangeOfRecycler;
    }
};

class Tile
{
    friend class MapManager;

public:
    Tile() {}
    ~Tile() {}

    bool IsEmpty() const { return m_properties.owner == -1; }
    bool IsMyTile() const { return m_properties.owner == 1; }
    bool IsOppTile() const { return m_properties.owner == 0; }

    bool HasRecycler() const { return m_properties.recycler == 1; }
    bool HasUnits() const { return m_properties.units > 0; }
    int GetUnits() const { return m_properties.units; }

    bool CanBuildRecycler() const { return m_properties.canBuild == 1; }
    bool CanSpawnRobot() const { return m_properties.canSpawn == 1; }
    bool IsInRangeOfRecycler() const { return m_properties.inRangeOfRecycler == 1; }

    const Vec2 GetPos() const { return { m_properties.x, m_properties.y }; }
    int GetScrapAmount() const { return m_properties.scrapAmount; }
    bool CanBuild(const EntityType entityType) const;

    std::string ToString() const
    {
        return m_properties.ToString();
    }

    bool operator==(const Tile& other) const
    {
        return m_properties == other.m_properties;
    }

private:
    TileProperties m_properties;
};

class MapManager
{
    friend class Game;

private:
    void CreateTile(const TileProperties& properties);
    const Tile& GetTile(const Vec2& pos) const;
    const Tile& GetTile(const TileProperties& properties) const;

    const std::vector<Tile>& GetTiles() const { return m_tiles; }

    bool CanBuild(const Vec2& pos, const EntityType entity) const;

private:
    Vec2 m_size;

    std::vector<Tile> m_tiles;
};