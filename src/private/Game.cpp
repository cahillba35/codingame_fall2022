#include "Game.hpp"

#include "ActionManager.hpp"
#include "EntityManager.hpp"
#include "MapManager.hpp"

#include <random>

// ----------------------------------------------
void Game::Init()
{
    // When game is initialized, the map size is given.
    // Note: two integers width and height for the size of the map. The top-left tile is (x,y) = (0,0).
    Vec2 mapSize = { 0, 0 };
    cin >> mapSize.x >> mapSize.y;
    cin.ignore();

    m_mapManager.m_size = mapSize;
}

// ----------------------------------------------
void Game::ProcessGameInput()
{
    // Read in how many resources each player has.
    // Note: two integers myMatter and oppMatter for the amount of matter owned by each player.
    int my_matter;
    int opp_matter;
    cin >> my_matter >> opp_matter;
    cin.ignore();

    UpdateMyMatter(my_matter);
    UpdateOppMatter(opp_matter);
    UpdateMySpentMatter(my_matter);

    // Clear all the old data.
    m_mapManager.m_tiles.clear();
    m_entityManager.m_entities.clear();
    m_actionManager.m_actions.clear();

    // Each loop we will get information for each tile on the map, recreate everything again with new state.
    // Note: (width * height) number of inputs, starting at (0,0) and incrementing from left to right, top to bottom. Each cell is represented by 7 integers.
    for (int y = 0; y < m_mapManager.m_size.y; y++)
    {
        for (int x = 0; x < m_mapManager.m_size.x; x++)
        {
            // Each tile has 7 properties.
            TileProperties p({ x, y });
            cin >> p.scrapAmount >> p.owner >> p.units >> p.recycler >> p.canBuild >> p.canSpawn >> p.inRangeOfRecycler;
            cin.ignore();

            // Update the tile with the new properties.
            m_mapManager.CreateTile(p);
        }
    }

    helpers::PrintDebugMessage("Tile count: " + std::to_string(m_mapManager.m_tiles.size()));
}

// ----------------------------------------------
void Game::CreateEntities()
{
    // Create entities from the map.
    m_entityManager.CreateEntities(*this);

    helpers::PrintDebugMessage("Created entity count: " + std::to_string(m_entityManager.m_entities.size()));
}

// ----------------------------------------------
void Game::CreateEntityActions()
{
    // Create actions for each entity.
    m_entityManager.CreateActions(*this);
}

// ----------------------------------------------
std::string Game::CreateActionString()
{
    // Send the actions to the game.
    return m_actionManager.CreateActionString();
}

// ----------------------------------------------
bool Game::CanBuild(const Vec2& pos, EntityType entityType) const
{
    return m_mapManager.CanBuild(pos, entityType);
}

// ----------------------------------------------
int Game::GetRandomBetween(int min, int max) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    return dis(gen);
}

// ----------------------------------------------
float Game::GetRandomBetween(float min, float max) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);

    return dis(gen);
}

// ----------------------------------------------
float Game::GetRandom() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0f, 1.0f);

    return dis(gen);
}