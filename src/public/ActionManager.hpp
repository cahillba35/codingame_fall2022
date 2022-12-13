#pragma once

#include "Vec2.hpp"

#include <iostream>
#include <vector>

using namespace std;

enum class ActionType
{
    ACTION_TYPE_NONE,

    ACTION_TYPE_MOVE,
    ACTION_TYPE_BUILD,
    ACTION_TYPE_SPAWN,
    ACTION_TYPE_WAIT,
    ACTION_TYPE_MESSAGE,

    ACTION_TYPE_COUNT
};

struct Action
{
    ActionType type;
    Vec2 from;
    Vec2 to;
    const char* message;
    uint8_t turnId;

    bool operator==(const Action& other) const
    {
        return turnId == other.turnId
            && type == other.type
            && from == other.from
            && to == other.to
            && message == other.message;
    }

    void Perform();
};

class ActionManager
{
public:
    ActionManager();
    ~ActionManager();

    static ActionManager& GetInstance()
    {
        static ActionManager instance;
        return instance;
    }

    void PerformActions();
    void AddAction(const Action& action);
    void RemoveAction(const Action& action);

    const vector<Action>& GetActions() const { return m_actions; }

private:
    vector<Action> m_actions;
};