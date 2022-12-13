#pragma once

#include "ActionManager.hpp"
#include "GameState.hpp"

#include "filters.hpp"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

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

    void Process() const;
};

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    static EntityManager& GetInstance()
    {
        static EntityManager instance;
        return instance;
    }

    void CreateEntitiesFromMap();
    void AddEntity(const Entity& entity);
    void RemoveEntity(const Entity& entity);

    void ProcessEntities();

    const vector<Entity>& GetEntities() const { return m_entities; }

    static const vector<Entity> GetMyRobots()
    {
        auto& entities = EntityManager::GetInstance().GetEntities();

        vector<Entity> myEntities;
        copy_if(entities.begin(), entities.end(), back_inserter(myEntities),
        [] (const Entity entity)
        {
            return entity.alliance == Alliance::ALLIANCE_MY
                && entity.type == EntityType::ENTITY_TYPE_ROBOT;
        });

        return myEntities;
    }

    static const vector<Entity> GetEnemyRobots()
    {
        auto& entities = EntityManager::GetInstance().GetEntities();

        vector<Entity> enemyEntities;
        copy_if(entities.begin(), entities.end(), back_inserter(enemyEntities), 
        [] (const Entity entity)
        { 
            return entity.alliance == Alliance::ALLIANCE_OPP
                && entity.type == EntityType::ENTITY_TYPE_ROBOT;
        });

        return enemyEntities;
    }

    static const Entity& GetNearestEnemyRobot(const Entity& entity)
    {
        EntityManager& entityManager = EntityManager::GetInstance();
        const vector<Entity>& enemyRobots = entityManager.GetEnemyRobots();

        // From the enemyRobots, find the closest one by manhattan distance
        auto closestEnemy = enemyRobots[0];
        int closestDistance = entity.position.ManhattanDistance(closestEnemy.position);
        for (auto& enemy : enemyRobots)
        {
            int distance = entity.position.ManhattanDistance(enemy.position);
            if (distance < closestDistance)
            {
                closestDistance = distance;
                closestEnemy = enemy;
            }
        }

        return closestEnemy;
    }

private:
    vector<Entity> m_entities;
};