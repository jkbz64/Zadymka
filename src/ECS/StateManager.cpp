#include <include/ECS/StateManager.hpp>
#include <iostream>

void StateManager::registerClass()
{
    Lua::getState().new_usertype<StateManager>("StateManager",
                                               "new", sol::no_constructor,
                                               "setState", &StateManager::setState,
                                               "popBack", &StateManager::popState,
                                               "getCurrentState", [](StateManager& mgr) -> const GameState&
                                               {
                                                   return mgr.getCurrentState();
                                               }

    );
}

void StateManager::setState(sol::table stateTable)
{
    m_gameStates.emplace(stateTable);
    if(stateTable["init"].valid())
    {
        GameState& state = m_gameStates.top();
        stateTable["init"].call(&state);
    }
}

void StateManager::popState()
{
    if(!m_gameStates.empty())
        m_gameStates.pop();
}
