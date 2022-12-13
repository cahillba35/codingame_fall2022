#include "../public/MapManager.hpp"
#include "../public/Vec2.hpp"

// ----------------------------------------------
MapManager::MapManager()
{
}

// ----------------------------------------------
MapManager::~MapManager()
{
}

// ----------------------------------------------
void Tile::Init(Vec2 pos)
{
    m_pos = pos;
}

// ----------------------------------------------
void Tile::SetProperties(TileProperties properties)
{
    m_properties = properties;
}

// ----------------------------------------------
void MapManager::Init(Vec2 size)
{
    m_size = size;

    m_tiles.resize(size.x * size.y);
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            m_tiles[y * size.x + x].Init({ x, y });
        }
    }
}

// ----------------------------------------------
void MapManager::UpdateTileProperties(const Vec2& pos, TileProperties properties)
{
    m_tiles[pos.y * m_size.x + pos.x].SetProperties(properties);
}

// ----------------------------------------------
const Tile& MapManager::GetTile(const Vec2& pos) const
{
    return m_tiles[pos.y * m_size.x + pos.x];
}