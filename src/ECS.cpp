#include <include/ECS.hpp>
#include <Lua.hpp>
#include <ECS/GameState.hpp>
#include <iostream>

namespace
{
    std::unordered_map<std::string, sol::table> m_registeredStates;
    std::unordered_map<std::string, sol::table> m_registeredComponents;
    std::unordered_map<std::string, sol::table> m_registeredEntities;
    std::unordered_map<std::string, sol::table> m_registeredSystems;
}

sol::table ECS::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module["init"] = &ECS::init;
    module["deinit"] = &ECS::deinit;
    GameState::registerClass(module);
    Entity::registerClass(module);
    EntityManager::registerClass(module);
    EventManager::registerClass(module);
    System::registerClass(module);
    
    module["registerState"] = &ECS::registerState;
    module["createState"] = &ECS::createState;
    module["registerComponent"] = &ECS::registerComponent;
    module["registerEntity"] = &ECS::registerEntity;
    module["registerSystem"] = &ECS::registerSystem;
    module["states"] = &m_registeredStates;
    module["components"] = &m_registeredComponents;
    module["entities"] = &m_registeredEntities;
    
    return module;
}

bool ECS::init(sol::this_state)
{
    return true;
}

void ECS::deinit()
{
    m_registeredStates.clear();
    m_registeredComponents.clear();
    m_registeredEntities.clear();
    m_registeredSystems.clear();
}

void ECS::registerState(const std::string &stateName, sol::table stateTable)
{
    m_registeredStates[stateName] = stateTable;
}

std::unique_ptr<GameState> ECS::createState(const std::string& stateName)
{
    if(m_registeredStates.find(stateName) != std::end(m_registeredStates))
        return std::make_unique<GameState>(m_registeredStates[stateName]);
    else
    {
        std::cerr << stateName << " has not been registered, returning nullState\n";
        return std::make_unique<GameState>();
    }
}

void ECS::registerComponent(const std::string &componentName, sol::table componentTable)
{
    m_registeredComponents[componentName] = componentTable;
}

void ECS::registerEntity(const std::string &entityName, sol::table entityTable)
{
    m_registeredEntities[entityName] = entityTable;
}

void ECS::registerSystem(const std::string &systemName, sol::table systemTable)
{
    m_registeredSystems[systemName] = systemTable;
}

sol::table ECS::getSystem(const std::string& systemName)
{
    return m_registeredSystems[systemName];
}

extern "C" int luaopen_Zadymka_ECS(lua_State* L)
{
    return sol::stack::call_lua(L, 1, ECS::createModule);
}