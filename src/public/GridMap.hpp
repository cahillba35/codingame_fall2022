#pragma once

#include "GridCell.hpp"
#include "Vec2.hpp"

#include <vector>

class GridMap
{
public:
    GridMap();
    ~GridMap();

    void Init(Vec2 size);

    static GridMap& GetInstance()
    {
        static GridMap instance;
        return instance;
    }

    Vec2 GetSize() const { return m_size; }

    GridCell& GetCell(const Vec2& pos);

private:
    Vec2 m_size = { 0, 0 };

    std::vector<GridCell> m_cells;
};