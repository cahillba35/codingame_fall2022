#include "../public/ActionManager.hpp"

#include "../public/helpers.hpp"

// ----------------------------------------------
std::string Action::AppendAction()
{
    std::string actionString = "";

    switch (type)
    {
        case ActionType::ACTION_TYPE_MOVE:
        {
            // Automatic pathfinding.
            actionString =  "MOVE " + 
            std::to_string(1) + " " + 
            std::to_string(from.x) + " " + 
            std::to_string(from.y) + " " + 
            std::to_string(to.x) + " " + 
            std::to_string(to.y);
            break;
        }

        case ActionType::ACTION_TYPE_BUILD:
        {
            // Builds a recycler.
            actionString = "BUILD " +
            std::to_string(from.x) + " " +
            std::to_string(from.y);
            break;
        }

        case ActionType::ACTION_TYPE_SPAWN:
        {
            // Adds unit to an owned tile.
            actionString = "SPAWN " +
            std::to_string(1) + " " +
            std::to_string(from.x) + " " +
            std::to_string(from.y);
            break;
        }

        case ActionType::ACTION_TYPE_WAIT:
        {
            // Does nothing.
            actionString = "WAIT";
            break;
        }

        case ActionType::ACTION_TYPE_MESSAGE:
        {
            // Displays text on your side of the HUD.
            // cout << "MESSAGE " << message << endl;
            actionString = "";
            break;
        }

        default: { actionString = ""; break;}
    }

    actionString += ";";
    return actionString;
}

// ----------------------------------------------
void ActionManager::AddAction(const Action& action)
{
    m_actions.push_back(action);
}

// ----------------------------------------------
std::string ActionManager::CreateActionString()
{
    std::string actionString = "";

    // use PrintDebugMessage to print the size of actions
    helpers::PrintDebugMessage("ActionManager::action count: " + std::to_string(m_actions.size()));

    for (auto& action : m_actions)
    {
        actionString += action.AppendAction();
    }

    if (actionString.empty())
    {
        actionString = "WAIT";
    }

    return actionString;
}