#include <ECS/EntityManager.hpp>
#include <sol/state_view.hpp>

std::unordered_map<std::string, sol::table> EntityManager::m_registeredEntities;
std::unordered_map<std::string, sol::table> EntityManager::m_registeredComponents;

void EntityManager::registerEntity(const std::string &name, sol::table entity)
{
    m_registeredEntities[name] = entity;
}

void EntityManager::registerComponent(const std::string &name, sol::table component)
{
    m_registeredComponents[name] = component;
}

EntityManager::EntityManager(sol::this_state L, EventManager& manager) :
    m_lua(L),
    m_eventManager(manager),
    m_uniqueID(1),
    m_nullEntity(nullptr, 0)
{

}

Entity& EntityManager::createEntity(const std::string& entityName)
{
    auto componentTable = m_registeredEntities[entityName];
    if(componentTable.valid())
        return createEntity(componentTable);
    else
    {
        std::puts(std::string("Entity" + entityName + "hasn't been registered. Returning nill entity").c_str());
        return m_nullEntity;
    }
}

Entity& EntityManager::createEntity(sol::table componentTable)
{
    const auto id = m_uniqueID++;
    auto inserted = m_entities.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(id),
                                       std::forward_as_tuple(this, id));
    auto it = inserted.first;
    auto& e = it->second;
    
    for(std::pair<sol::object, sol::table> pair : componentTable)
    {
        std::string componentName = pair.first.as<std::string>();
        e.addComponent(componentName, pair.second);
    }
    m_eventManager.emit("EntityCreated", m_lua.create_table_with("entity", &e));
    return e;
}

void EntityManager::destroyEntity(std::size_t id)
{
    auto& entity = m_entities.at(id);
    m_eventManager.emit("EntityDestroyed", m_lua.create_table_with("entity", &entity));
    m_entities.erase(id);
}

Entity& EntityManager::getEntity(std::size_t id)
{
    if(m_entities.find(id) != m_entities.end())
        return m_entities.find(id)->second;
    else
        return m_nullEntity;
}

sol::table EntityManager::getDefaultComponent(const std::string& componentName)
{
    return m_registeredComponents[componentName];
}
