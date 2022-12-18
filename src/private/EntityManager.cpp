#include "../public/EntityManager.hpp"

#include "../public/Game.hpp"
#include "../public/MapManager.hpp"

#include "../public/helpers.hpp"

namespace
{
    Alliance GetEntityAlliance(const Tile& tile)
    {
        Alliance alliance = Alliance::ALLIANCE_NONE;
        if (tile.IsMyTile())
        {
            alliance = Alliance::ALLIANCE_MY;
        }
        else if (tile.IsOppTile())
        {
            alliance = Alliance::ALLIANCE_OPP;
        }

        return alliance;
    }
}

// ----------------------------------------------
EntityManager::EntityManager()
{
}

// ----------------------------------------------
EntityManager::~EntityManager()
{
}

// ----------------------------------------------
void EntityManager::CreateEntities(const Game& game)
{
    // Loop through the map and create new entities that are at each tile.
    for (int y = 0; y < game.GetMapSize().y; ++y)
    {
        for (int x = 0; x < game.GetMapSize().x; ++x)
        {
            const Tile& tile = game.GetTile({ x, y });

            // A tile can have a recycler or units, not both.
            if (tile.HasRecycler())
            {
                Entity entity;
                entity.type = EntityType::ENTITY_TYPE_RECYCLER;
                entity.alliance = GetEntityAlliance(tile);
                entity.position = { x, y };
                AddEntity(entity);
            }
            else if (tile.HasUnits())
            {
                for (int i = 0; i < tile.GetUnits(); ++i)
                {
                    Entity entity;
                    entity.type = EntityType::ENTITY_TYPE_ROBOT;
                    entity.alliance = GetEntityAlliance(tile);
                    entity.position = { x, y };
                    AddEntity(entity);
                }
            }
        }
    }
}

// ----------------------------------------------
void EntityManager::AddEntity(const Entity& entity)
{
    m_entities.push_back(entity);
}

// ----------------------------------------------
void EntityManager::CreateActions(Game& game)
{
    const vector<Entity> myRobots = GetMyRobots();

    helpers::PrintDebugMessage("My robots: " + std::to_string(myRobots.size()));

    for (const Entity robot : myRobots)
    {
        // For now, move this entity to the nearest enemy robot
        const vector<Entity> enemyRobots = GetEnemyRobots();
        if (enemyRobots.size() < 1)
        {
            // No enemy robots, so do nothing
            continue;
        }
        const Entity nearestEnemy = GetNearestEnemyRobot(robot);

        // Create an action to move to the nearest enemy
        Action action;
        action.type = ActionType::ACTION_TYPE_MOVE;
        action.from = robot.position;
        action.to = nearestEnemy.position;
        action.turnId = game.GetTurn();
        game.AddAction(action);
    }

    helpers::PrintDebugMessage("Done creating actions!");
}

// ----------------------------------------------
const vector<Entity>& EntityManager::GetEntities() const
{
    return m_entities;
}

// ----------------------------------------------
const vector<Entity> EntityManager::GetMyRobots() const
{
    vector<Entity> myRobots;

    for (const Entity& entity : m_entities)
    {
        if (entity.alliance == Alliance::ALLIANCE_MY
            && entity.type == EntityType::ENTITY_TYPE_ROBOT)
        {
            myRobots.push_back(entity);
        }
    }

    return myRobots;
}

// ----------------------------------------------
const vector<Entity> EntityManager::GetMyRecyclers() const
{
    vector<Entity> myRecyclers;

    for (const Entity& entity : m_entities)
    {
        if (entity.alliance == Alliance::ALLIANCE_MY
            && entity.type == EntityType::ENTITY_TYPE_RECYCLER)
        {
            myRecyclers.push_back(entity);
        }
    }

    return myRecyclers;
}

// ----------------------------------------------
const vector<Entity> EntityManager::GetEnemyRobots() const
{
    vector<Entity> enemyRobots;

    for (const Entity& entity : m_entities)
    {
        if (entity.alliance == Alliance::ALLIANCE_OPP
            && entity.type == EntityType::ENTITY_TYPE_ROBOT)
        {
            enemyRobots.push_back(entity);
        }
    }

    return enemyRobots;
}

// ----------------------------------------------
const vector<Entity> EntityManager::GetEnemyRecyclers() const
{
    vector<Entity> enemyRecyclers;

    for (const Entity& entity : m_entities)
    {
        if (entity.alliance == Alliance::ALLIANCE_OPP
            && entity.type == EntityType::ENTITY_TYPE_RECYCLER)
        {
            enemyRecyclers.push_back(entity);
        }
    }

    return enemyRecyclers;
}

// ----------------------------------------------
const Entity EntityManager::GetNearestEnemyRobot(const Entity robot) const
{
    const vector<Entity> enemyRobots = GetEnemyRobots();
    if(enemyRobots.size() < 1)
    {
        // No enemy robots, so return the first robot
        Entity entity;
        entity.position = { 0, 0 };
        return entity;
    }

    // Find the nearest enemy robot
    int nearestDistance = 9999;
    Entity nearestEnemy = enemyRobots[0];
    for (const Entity enemy : enemyRobots)
    {
        const int distance = robot.position.ManhattanDistance(enemy.position);
        if (distance < nearestDistance)
        {
            nearestDistance = distance;
            nearestEnemy = enemy;
        }
    }

    return nearestEnemy;
}