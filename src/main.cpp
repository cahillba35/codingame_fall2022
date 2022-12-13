#include "public/ActionManager.hpp"
#include "public/EntityManager.hpp"
#include "public/GameState.hpp"
#include "public/MapManager.hpp"
#include "public/Vec2.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Note: This is a simple example of how to use the cpp-merge tool.
// cpp-merge --include ../codingame_fall2022/src/public --source ../codingame_fall2022/src/private --output ../codingame_fall2022/src/output.txt ../codingame_fall2022/src/main.cpp

int main()
{
    // When game is initialized, the map size is given.
    Vec2 mapSize = { 0, 0 };
    cin >> mapSize.x >> mapSize.y;
    cin.ignore();

    cerr << "map size got" << endl;

    // Initialize the GridMap. This will create all the GridCells.
    MapManager::GetInstance().Init(mapSize);

    // Advance Game Loop
    while (1)
    {
        cerr << "1.0" << endl;
        // Each loop we will get the current state of the game. Update our GameState.
        int my_matter;
        cerr << "1.0.1" << endl;
        int opp_matter;
        cerr << "1.0.2" << endl;
        cin >> my_matter >> opp_matter;
        cerr << "1.0.3" << endl;
        cin.ignore();

cerr << "1.1" << endl;

        GameState& gameState = GameState::GetInstance();
        cerr << "1.2" << endl;
        gameState.EnableDebugMessages(false);
        cerr << "1.3" << endl;
        gameState.IncrementTurn();
        cerr << "1.4" << endl;
        gameState.UpdateMyMatter(my_matter);
        cerr << "1.5" << endl;
        gameState.UpdateOppMatter(opp_matter);
        cerr << "1.6" << endl;
cerr << "2.0" << endl;
        // Each loop we will get information for each tile on the map. Update our MapManager's Tiles.
        MapManager mapManager = MapManager::GetInstance();
        Vec2 size = mapManager.GetSize();
        for (int y = 0; y < size.y; y++)
        {
            for (int x = 0; x < size.x; x++)
            {
                // Each tile has 7 properties.
                TileProperties p;
                cin >> p.scrapAmount >> p.owner >> p.units >> p.recycler >> p.canBuild >> p.canSpawn >> p.inRangeOfRecycler;
                cin.ignore();

                // Update the tile at position { x, y } with the properties p.
                mapManager.UpdateTileProperties({ x, y }, p);
            }
        }
        
cerr << "3.0" << endl;
        // Each loop we will process entities.
        EntityManager entityManager = EntityManager::GetInstance();
cerr << "4.0" << endl;
        // Clear and recreate all entities from current map state.
        entityManager.CreateEntitiesFromMap(); 

        // Each Entity will process map state and make an action.
        entityManager.ProcessEntities();
cerr << "5.0" << endl;
        // Perform all actions that were created.
        ActionManager actionManager = ActionManager::GetInstance();
        actionManager.PerformActions();
    }
}