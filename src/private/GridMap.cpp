#include "../public/GridMap.hpp"

// ----------------------------------------------
GridMap::GridMap ()
{
}

// ----------------------------------------------
GridMap::~GridMap ()
{
}

// ----------------------------------------------
void GridMap::Init (Vec2 size)
{
    m_size = size;

    m_cells.resize(m_size.x * m_size.y);
    for (int y = 0; y < m_size.y; y++)
    {
        for (int x = 0; x < m_size.x; x++)
        {
            m_cells[y * m_size.x + x].Init({ x, y });
        }
    }
}

// ----------------------------------------------
GridCell& GridMap::GetCell (const Vec2& pos)
{
    return m_cells[pos.y * m_size.x + pos.x];
}