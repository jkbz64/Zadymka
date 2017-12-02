#include <include/ECS.hpp>
#include <ECS/StateManager.hpp>

namespace
{
    std::unordered_map<std::string, sol::table> m_registeredStates;
    std::unordered_map<std::string, sol::table> m_registeredComponents;
    std::unordered_map<std::string, sol::table> m_registeredEntities;
}

void ECS::registerModule()
{
    StateManager::registerClass();
    GameState::registerClass();
    Entity::registerClass();
    EntityManager::registerClass();
    EventManager::registerClass();
    System::registerClass();
}

bool ECS::init()
{
    Lua::getState()["ECS"] = Lua::getState().create_table_with(
            "registerState", &ECS::registerState,
            "registerComponent", &ECS::registerComponent,
            "registerEntity", &ECS::registerEntity,
            "states", &m_registeredStates,
            "components", &m_registeredComponents,
            "entities", &m_registeredEntities
    );
    return true;
}

void ECS::deinit()
{
    m_registeredStates.clear();
    m_registeredComponents.clear();
    m_registeredEntities.clear();
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

