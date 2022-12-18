#pragma once

#include "ActionManager.hpp"
#include "EntityManager.hpp"
#include "MapManager.hpp"

#include "vec2.hpp"

class Tile;

struct GameState
{
    unsigned char turn = 0;
    int myMatter = 0;
    int oppMatter = 0;

    int mySpentMatter = 0;
};

class Game
{
public:
    Game() {}
    ~Game() {}

    void Init();
    void ProcessGameInput();
    void CreateEntities();
    void CreateEntityActions();
    std::string CreateActionString();

    void IncrementTurn() { m_gameState.turn++; }
    unsigned char GetTurn() const { return m_gameState.turn; }

    int GetMyMatter() const { return m_gameState.myMatter; }
    int GetMySpentMatter() const { return m_gameState.mySpentMatter; }
    void PayMatter(int matter) { m_gameState.mySpentMatter -= matter; }

    int GetRandomBetween(int min, int max) const;
    float GetRandomBetween(float min, float max) const;
    float GetRandom() const;

    // Building things.
    bool CanBuild(const Vec2& pos, EntityType entityType) const;

    // Map things.
    Vec2 GetMapSize() const { return m_mapManager.m_size; }
    const vector<Tile> GetTiles() const { return m_mapManager.GetTiles(); }
    const Tile GetTile(const Vec2& pos) const { return m_mapManager.GetTile(pos); }

    // Entity things.
    const vector<Entity> GetEntities() const { return m_entityManager.GetEntities(); }
    const vector<Entity> GetMyRobots() const { return m_entityManager.GetMyRobots(); }
    const vector<Entity> GetMyRecyclers() const { return m_entityManager.GetMyRecyclers(); }
    const vector<Entity> GetEnemyRobots() const { return m_entityManager.GetEnemyRobots(); }

    // Action things.
    void AddAction(const Action& action) { m_actionManager.AddAction(action); }

private:
    void UpdateMyMatter(int matter) { m_gameState.myMatter = matter; }
    void UpdateOppMatter(int matter) { m_gameState.oppMatter = matter; }
    void UpdateMySpentMatter(int matter) { m_gameState.mySpentMatter = matter; }

private:
    GameState m_gameState;
    ActionManager m_actionManager;
    EntityManager m_entityManager;
    MapManager m_mapManager;
};