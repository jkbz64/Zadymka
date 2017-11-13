#include <StateManager.hpp>
#include <iostream>

void StateManager::registerClass()
{
    Lua::getState().new_usertype<StateManager>("StateManager",
                                               "new", sol::no_constructor,
                                               "setState", &StateManager::setState,
                                               "popBack", &StateManager::popState,
                                               "getCurrentState", [](StateManager& mgr)
                                               {
                                                   return mgr.getCurrentState().getState();
                                               }

    );
}

void StateManager::setState(const std::string& name)
{
    sol::object state;
    try
    {
        state = Lua::scriptArgs("return dofile('states/' .. arg[1] .. '.lua')", name);
    }
    catch(sol::error& e)
    {
        std::cerr << e.what() << "\n";
        return;
    }
    m_gameStates.emplace(state);
}

void StateManager::popState()
{
    if(!m_gameStates.empty())
        m_gameStates.pop();
}
