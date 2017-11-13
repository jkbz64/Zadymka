#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP
#include <GameState.hpp>
#include <stack>

class StateManager
{
public:
    static void registerClass();
    StateManager();
    ~StateManager() = default;
    const GameState& getCurrentState() const;
    void setState(const std::string&);
    void popState();
private:
    std::stack<GameState> m_gameStates;
    GameState m_nullState;
};

inline const GameState& StateManager::getCurrentState() const
{
    if(m_gameStates.empty())
        return m_nullState;
    else
        return m_gameStates.top();
}

#endif
