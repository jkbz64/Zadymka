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

void StateManager::setState(const std::string& name)
{
    sol::object state = Lua::getState().script("return dofile('states/" + name + ".lua')()");
}

GameState& StateManager::getCurrentState()
{
    if(m_gameStates.empty())
        return m_nullState;
    else
        return m_gameStates.front();
}
