#include <include/ECS.hpp>
#include <ECS/StateManager.hpp>
#include <Lua.hpp>

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
    StateManager::registerClass(module);
    GameState::registerClass(module);
    Entity::registerClass(module);
    EntityManager::registerClass(module);
    EventManager::registerClass(module);
    System::registerClass(module);
    return module;
}

bool ECS::init()
{
    Lua::getState()["ECS"] = Lua::getState().create_table_with(
            "registerState", &ECS::registerState,
            "registerComponent", &ECS::registerComponent,
            "registerEntity", &ECS::registerEntity,
            "registerSystem", &ECS::registerSystem,
            "states", &m_registeredStates,
            "components", &m_registeredComponents,
            "entities", &m_registeredEntities,
            "systems", &m_registeredSystems
    );
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