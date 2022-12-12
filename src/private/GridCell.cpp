#include "../public/GridCell.hpp"

// ----------------------------------------------
GridCell::GridCell ()
{
}

// ----------------------------------------------
GridCell::~GridCell ()
{
}

// ----------------------------------------------
void GridCell::Init (Vec2 pos)
{
    m_pos = pos;
}

// ----------------------------------------------
void GridCell::Update (GridCellProperties properties)
{
    m_properties = properties;
}
