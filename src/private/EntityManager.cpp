#include "../public/EntityManager.hpp"

#include "../public/MapManager.hpp"

namespace
{
    Alliance GetTileAlliance(const Tile& tile)
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
void Entity::Process() const
{
        GameState gameState = GameState::GetInstance();

        // For now, move this entity to the nearest enemy robot
        EntityManager entityManager = EntityManager::GetInstance();
        const vector<Entity>& enemyRobots = entityManager.GetEnemyRobots();
        const Entity& nearestEnemy = EntityManager::GetNearestEnemyRobot(*this);

        // Create an action to move to the nearest enemy
        Action action;
        action.type = ActionType::ACTION_TYPE_MOVE;
        action.from = position;
        action.to = nearestEnemy.position;
        action.turnId = gameState.GetTurn();

        // Add the action to the action manager
        ActionManager::GetInstance().AddAction(action);

        // Print the action to the console
        if (gameState.DebugMessagesEnabled())
        {
            cout << "Moving from " << action.from.x << ", " << action.from.y << " to " << action.to.x << ", " << action.to.y << endl;
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
void EntityManager::CreateEntitiesFromMap()
{
    // Clear out the old entities. We will make new ones from the state of the map.
    m_entities.clear();

    cerr << "c1.0" << endl;

    // Get the map.
    MapManager& mapManager = MapManager::GetInstance();
    Vec2 mapSize = mapManager.GetSize();
    cerr << "c1.0 " << mapSize.x << " " << mapSize.y << endl;
    for (int y = 0; y < mapSize.y; ++y)
    {
        cerr << "y " << y << endl;
        for (int x = 0; x < mapSize.x; ++x)
        {
            cerr << "x " << x << endl;
            Vec2 pos(x, y);
            const Tile& tile = mapManager.GetTile(pos);
            // print the position of this tile and how many units are at this time
            cerr << "This tile: " << pos.x << " " << pos.y << " " << tile.GetUnits() << endl;

            // A tile can have a recycler or units, not both.
            if (tile.HasRecycler())
            {
                Entity entity;
                entity.type = EntityType::ENTITY_TYPE_RECYCLER;
                entity.alliance = GetTileAlliance(tile);
                AddEntity(entity);
            }
            else if (tile.HasUnits())
            {
                for (int i = 0; i < tile.GetUnits(); ++i)
                {
                    Entity entity;
                    entity.type = EntityType::ENTITY_TYPE_ROBOT;
                    entity.alliance = GetTileAlliance(tile);
                    AddEntity(entity);
                }
            }
        }
    }
}

// ----------------------------------------------
void EntityManager::AddEntity(const Entity& entity)
{
    m_entities.emplace_back(entity);
}

// ----------------------------------------------
void EntityManager::RemoveEntity(const Entity& entity)
{
    auto it = find(m_entities.begin(), m_entities.end(), entity);
    if (it != m_entities.end())
    {
        m_entities.erase(it);
    }
}

// ----------------------------------------------
void EntityManager::ProcessEntities()
{
    cerr << "e1.0" << endl;

    const auto& myRobots = GetMyRobots();
    cerr << "e1.1 " << myRobots.size() << endl;

    for (auto&& robot : myRobots)
    {
        robot.Process();
    }
}