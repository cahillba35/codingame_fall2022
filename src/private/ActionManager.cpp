#include "../public/ActionManager.hpp"

// ----------------------------------------------
void Action::Perform()
{
    switch (type)
    {
        case ActionType::ACTION_TYPE_MOVE:
        {
            // Automatic pathfinding.
            cout << "MOVE " << 1 << " " << from.x << " " << from.y << " " << to.x << " " << to.y << endl;
            break;
        }

        case ActionType::ACTION_TYPE_BUILD:
        {
            // Builds a recycler.
            cout << "BUILD " << from.x << " " << from.y << endl;
            break;
        }

        case ActionType::ACTION_TYPE_SPAWN:
        {
            // Adds unit to an owned tile.
            cout << "SPAWN " << 1 << " " << from.x << " " << from.y << endl;
            break;
        }

        case ActionType::ACTION_TYPE_WAIT:
        {
            // Does nothing.
            cout << "WAIT" << endl;
            break;
        }

        case ActionType::ACTION_TYPE_MESSAGE:
        {
            // Displays text on your side of the HUD.
            cout << "MESSAGE " << message << endl;
            break;
        }

        default: { break;}
    }
}

// ----------------------------------------------
ActionManager::ActionManager()
{
}

// ----------------------------------------------
ActionManager::~ActionManager()
{
}

// ----------------------------------------------
void ActionManager::PerformActions()
{
    cerr << "p1.0 " << m_actions.size() << endl;
    for (auto& action : m_actions)
    {
        action.Perform();
    }
}

// ----------------------------------------------
void ActionManager::AddAction(const Action& action)
{
    m_actions.emplace_back(action);
}

// ----------------------------------------------
void ActionManager::RemoveAction(const Action& action)
{
    auto it = find(m_actions.begin(), m_actions.end(), action);
    if (it != m_actions.end())
    {
        m_actions.erase(it);
    }
}