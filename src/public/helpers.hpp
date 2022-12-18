#pragma once

#include "EntityManager.hpp"
#include "Game.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace helpers
{
    static void PrintDebugMessage(std::string message)
    {
        std::cerr << message << endl;
    }
}