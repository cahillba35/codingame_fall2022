#pragma once

#include "vec2.hpp"

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
    ActionType type = ActionType::ACTION_TYPE_NONE;
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

    std::string ActionTypeToString() const
    {
        switch (type)
        {
            case ActionType::ACTION_TYPE_MOVE: { return "MOVE"; }
            case ActionType::ACTION_TYPE_BUILD: { return "BUILD"; }
            case ActionType::ACTION_TYPE_SPAWN: { return "SPAWN"; }
            case ActionType::ACTION_TYPE_WAIT: { return "WAIT"; }
            case ActionType::ACTION_TYPE_MESSAGE: { return "MESSAGE"; }
            default: { return ""; }
        }
    }

    std::string ToString() const
    {
        std::string s = "Action: ";
        s += "type: " + ActionTypeToString() + ", ";
        s += "from: " + from.ToString() + ", ";
        s += "to: " + to.ToString() + ", ";
        s += "turnId: " + std::to_string(turnId);
        return s;
    }

    std::string AppendAction();
};

class ActionManager
{
    friend class Game;

private:
    void AddAction(const Action& action);

    std::string CreateActionString();

    const vector<Action>& GetActions() const { return m_actions; }

private:
    vector<Action> m_actions;
};