#include <StateManager.hpp>

void StateManager::exposeToLua()
{

}

StateManager::StateManager() :
    Scriptable<StateManager>()
{

}
