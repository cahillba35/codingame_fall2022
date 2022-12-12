#include "GameState.hpp"


// ----------------------------------------------
GameState::GameState ()
{
}

// ----------------------------------------------
GameState::~GameState ()
{
}

// ----------------------------------------------
void GameState::UpdateMyMatter (int matter)
{
    m_myMatter = matter;
}

// ----------------------------------------------
void GameState::UpdateOppMatter (int matter)
{
    m_oppMatter = matter;
}