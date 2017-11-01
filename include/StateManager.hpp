#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP
#include <Scriptable.hpp>
#include <GameState.hpp>

class StateManager : public Scriptable<StateManager>
{
public:
    static void exposeToLua();
    StateManager();
    void setState(const std::string&);
    GameState& getCurrentState();
private:
    std::vector<GameState> m_gameStates;
    GameState m_nullState;
};

#endif
