#pragma once

class GameState
{
public:
    GameState() {}
    ~GameState() {}

    static GameState& GetInstance()
    {
        static GameState instance;
        return instance;
    }

    void EnableDebugMessages(bool enable) { m_debugMessagesEnabled = enable; }
    bool DebugMessagesEnabled() const { return m_debugMessagesEnabled; }

    void IncrementTurn() { m_turn++; }
    unsigned char GetTurn() const { return m_turn; }
    void UpdateMyMatter(int matter) { m_myMatter = matter; }
    void UpdateOppMatter(int matter) { m_oppMatter = matter; }

private:
    unsigned char m_turn = 0;
    int m_myMatter = 0;
    int m_oppMatter = 0;

    bool m_debugMessagesEnabled = false;
};