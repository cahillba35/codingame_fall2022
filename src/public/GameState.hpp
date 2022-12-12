#pragma once

class GameState
{
public:
    GameState();
    ~GameState();

    static GameState& GetInstance()
    {
        static GameState instance;
        return instance;
    }

    void UpdateMyMatter(int matter);
    void UpdateOppMatter(int matter);

private:
    int m_myMatter = 0;
    int m_oppMatter = 0;
};