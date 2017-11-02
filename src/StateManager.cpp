#include <StateManager.hpp>

void StateManager::exposeToLua()
{
    Lua::getState().new_usertype<StateManager>("StateManager",
                                               "new", sol::no_constructor,
                                               "setState", &StateManager::setState
    );
}

StateManager::StateManager() :
    Scriptable<StateManager>()
{

}

#include <iostream>

void StateManager::setState(const std::string& name)
{
    sol::object state = Lua::getState().script("return dofile('states/" + name + ".lua')()");
    bool subclassOfGameState = Lua::getState().script("local state = dofile('states/" + name + ".lua') return state.super.name == 'GameState'");
    if(subclassOfGameState)
        m_gameStates.emplace_back(state);
    else
        std::cerr << name + " is not subclass of GameState\n";
}

GameState& StateManager::getCurrentState()
{
    if(m_gameStates.empty())
        return m_nullState;
    else
        return m_gameStates.front();
}
