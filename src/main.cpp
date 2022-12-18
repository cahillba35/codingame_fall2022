#include "../public/vec2.hpp"
#include "../public/helpers.hpp"

#include "public/Game.hpp"

#include "public/ActionManager.hpp"
#include "public/EntityManager.hpp"
#include "public/MapManager.hpp"

#include "public/helpers.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Note: This is a simple example of how to use the cpp-merge tool.
// cpp-merge --include ../codingame_fall2022/src/public --source ../codingame_fall2022/src/private --output ../codingame_fall2022/src/output.txt ../codingame_fall2022/src/main.cpp

int main()
{
    Game game = Game();
    game.Init();

    // Advance Game Loop
    while (1)
    {
        // Each loop we will get the current state of the game. Update our GameState.
        game.ProcessGameInput();

        // Create an entity for each unit on the map.
        game.CreateEntities();

        // TODO: Create BuildManager and move this logic there.

        // Do we have enough scrap to build a recycler?
        bool builtOneRecycler = false;
        while (game.GetMySpentMatter() >= 10)
        {
            helpers::PrintDebugMessage("My Matter: " + to_string(game.GetMyMatter()));
            helpers::PrintDebugMessage("My Spent Matter: " + to_string(game.GetMySpentMatter()));

            // Get one our robots and spawn another robot on top of it.
            const vector<Entity> myRobots = game.GetMyRobots();
            const vector<Entity> myRecyclers = game.GetMyRecyclers();
            const vector<Entity> enemyRobots = game.GetEnemyRobots();

            const vector<Tile> mapTiles = game.GetTiles();
            vector<Tile> myTiles;
            for(auto tile : mapTiles)
            {
                if (tile.IsMyTile())
                {
                    myTiles.push_back(tile);
                }
            }

            // Get a random tile
            int randomIndex = game.GetRandomBetween(0, myTiles.size() - 1);
            if (myTiles.size() < 1)
            {
                continue;
            }

            Tile randomTile = myTiles[randomIndex];

            // Decide what action to take, spawn a recycler or a robot.
            Action action;
            if (myRecyclers.size() < 1 && !builtOneRecycler && game.CanBuild(randomTile.GetPos(), EntityType::ENTITY_TYPE_RECYCLER))
            {
                // Spawn a recycler at the random tile.
                action.type = ActionType::ACTION_TYPE_SPAWN;
                action.from = randomTile.GetPos();
                action.to = Vec2(0, 0);
                action.turnId = game.GetTurn();
                game.AddAction(action);
                game.PayMatter(10);
                builtOneRecycler = true;
            }

            // If a recycler was not built this turn, then build robots.
            if (!builtOneRecycler && game.CanBuild(randomTile.GetPos(), EntityType::ENTITY_TYPE_ROBOT))
            {
                // Spawn a robot at the random tile.
                action.type = ActionType::ACTION_TYPE_SPAWN;
                action.from = randomTile.GetPos();
                action.to = Vec2(0, 0);
                action.turnId = game.GetTurn();
                game.AddAction(action);
                game.PayMatter(10);
            }

            if (action.type == ActionType::ACTION_TYPE_NONE)
            {
                break;
            }

            helpers::PrintDebugMessage("Build Action Performed: " + action.ToString());
        }

        // Create actions for each entity.
        game.CreateEntityActions();

        // Perform all actions that were created.
        cout << game.CreateActionString() << endl;

        // Increment the turn.
        game.IncrementTurn();
    }
}