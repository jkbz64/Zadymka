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

void StateManager::setState(const std::string& name)
{
    sol::table stateTable;
    try
    {
        stateTable = Lua::scriptArgs("return dofile('states/' .. arg[1] .. '.lua')", name);
    }
    catch(sol::error& e)
    {
        std::cerr << e.what() << "\n";
        return;
    }
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
