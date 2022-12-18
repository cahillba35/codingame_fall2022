#pragma once

#include "vec2.hpp"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

class Game;

using namespace std;

enum class Alliance
{
    ALLIANCE_NONE,

    ALLIANCE_MY,
    ALLIANCE_OPP,

    ALLIANCE_COUNT
};

enum class EntityType
{
    ENTITY_TYPE_NONE,

    ENTITY_TYPE_ROBOT,
    ENTITY_TYPE_RECYCLER,

    ENTITY_TYPE_COUNT
};

struct Entity
{
    EntityType type;
    Alliance alliance;
    Vec2 position;

    bool operator==(const Entity& other) const
    {
        return type == other.type
            && alliance == other.alliance
            && position == other.position;
    }
};

class EntityManager
{
    friend class Game;

private:
    EntityManager();
    ~EntityManager();

    void CreateEntities(const Game& game);
    void AddEntity(const Entity& entity);

    void CreateActions(Game& game);

    const vector<Entity>& GetEntities() const;
    const vector<Entity> GetMyRobots() const;
    const vector<Entity> GetMyRecyclers() const;
    const vector<Entity> GetEnemyRobots() const;
    const vector<Entity> GetEnemyRecyclers() const;

    const Entity GetNearestEnemyRobot(const Entity robot) const;

private:
    vector<Entity> m_entities;
};