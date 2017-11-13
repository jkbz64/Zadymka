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
    void setState(const std::string&);
    void popState();
    GameState& getCurrentState();
private:
    std::stack<GameState> m_gameStates;
    GameState m_nullState;
};

#endif
