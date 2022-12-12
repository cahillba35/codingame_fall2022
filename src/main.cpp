
#include "public/GameState.hpp"
#include "public/GridCell.hpp"
#include "public/GridMap.hpp"

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

    // Initialize the GridMap. This will create all the GridCells.
    GridMap::GetInstance().Init(mapSize);

    // game loop
    while (1)
    {
        // Each loop we will get the current state of the game. Update our GameState.
        int my_matter;
        int opp_matter;
        cin >> my_matter >> opp_matter;
        cin.ignore();

        GameState gameState = GameState::GetInstance();
        gameState.UpdateMyMatter(my_matter);
        gameState.UpdateOppMatter(opp_matter);

        // Each loop we will get information for each cell on the map. Update our GridMap's GridCells.
        GridMap gridMap = GridMap::GetInstance();
        Vec2 size = gridMap.GetSize();
        for (int y = 0; y < size.y; y++)
        {
            for (int x = 0; x < size.x; x++)
            {
                // Each cell has 7 properties.
                GridCellProperties p;
                cin >> p.scrapAmount >> p.owner >> p.units >> p.recycler >> p.canBuild >> p.canSpawn >> p.inRangeOfRecycler;
                cin.ignore();

                // Update the GridCell at this position.
                GridCell& cell = gridMap.GetCell({ x, y });
                cell.Update(p);
            }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << "WAIT" << endl;
    }
}