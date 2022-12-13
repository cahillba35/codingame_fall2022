#pragma once

struct Vec2
{
    int x;
    int y;

    Vec2() : x(0), y(0) {}
    Vec2(int x, int y) : x(x), y(y) {}

    bool operator==(const Vec2& other) const
    {
        return x == other.x
            && y == other.y;
    }

    int ManhattanDistance(const Vec2& other) const
    {
        return abs(x - other.x) + abs(y - other.y);
    }
};