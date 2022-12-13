#pragma once

#include "ActionManager.hpp"
#include "GameState.hpp"

#include <iostream>

using namespace std;

class DebugManager
{
public:
    DebugManager();
    ~DebugManager();

    static DebugManager& GetInstance()
    {
        static DebugManager instance;
        return instance;
    }

    static void DebugPrintMessage(const char* message)
    {
        // To debug: cerr << "Debug messages..." << endl;
        cerr << message << endl;
    }

    static void ActionPrintMessage(const char* message)
    {
        ActionManager actionManager = ActionManager::GetInstance();
        GameState gameState = GameState::GetInstance();

        // Create an action to print a message
        Action action;
        action.type = ActionType::ACTION_TYPE_MESSAGE;
        action.message = message;
        action.turnId = gameState.GetTurn();

        // Add the action to the action manager
        actionManager.AddAction(action);
    }
};