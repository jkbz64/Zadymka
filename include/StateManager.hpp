#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP
#include <GameState.hpp>

class StateManager
{
public:
    static void registerClass();
    StateManager();
    void setState(const std::string&);
    void popState();
    GameState& getCurrentState();
private:
    std::vector<GameState> m_gameStates;
    GameState m_nullState;
};

#endif
