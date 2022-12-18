#include "../public/MapManager.hpp"

#include "../public/Game.hpp"

#include "../public/helpers.hpp"

// ----------------------------------------------
// Tile
// ----------------------------------------------
bool Tile::CanBuild(const EntityType entityType) const
{
    if (entityType == EntityType::ENTITY_TYPE_RECYCLER)
    {
        return CanBuildRecycler();
    }
    else if (entityType == EntityType::ENTITY_TYPE_ROBOT)
    {
        return CanSpawnRobot();
    }
    else
    {
        return false;
    }
}

// ----------------------------------------------
void MapManager::CreateTile(const TileProperties& properties)
{
    Tile tile;
    tile.m_properties = properties;

    m_tiles.push_back(tile);
}

// ----------------------------------------------
const Tile& MapManager::GetTile(const Vec2& pos) const
{
    return m_tiles[pos.y * m_size.x + pos.x];
}

// ----------------------------------------------
const Tile& MapManager::GetTile(const TileProperties& properties) const
{
    return GetTile(Vec2(properties.x, properties.y));
}

// ----------------------------------------------
bool MapManager::CanBuild(const Vec2& pos, const EntityType entity) const
{
    return GetTile(pos).CanBuild(entity);
}