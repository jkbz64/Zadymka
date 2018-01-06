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
    m_nullEntity(nullptr, nullptr, 0)
{

}

EntityManager::~EntityManager()
{
    for(auto it = m_entities.cbegin(); it != m_entities.cend(); ++it)
    {
        destroyEntity(it->first);
    }
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

Entity& EntityManager::createEntity(const std::string &entityName, sol::table table)
{
    auto& componentTable = m_registeredEntities[entityName];
    if(componentTable.valid())
    {
        auto& entity = generateEntity();
        for(std::pair<sol::object, sol::table> pair : componentTable)
        {
            std::string componentName = pair.first.as<std::string>();
            entity.addComponent(componentName, pair.second);
        }
        if(table.valid())
        {
            for(const std::pair<sol::object, sol::object> &pair : table)
            {
                const auto componentName = pair.first.as<std::string>();
                if(entity.hasComponent(componentName))
                {
                    auto customComponent = pair.second.as<sol::table>();
                    sol::table component = entity.getComponent(componentName);
                    for(std::pair<sol::object, sol::object> &customPair : customComponent)
                    {
                        const auto varName = customPair.first.as<std::string>();
                        sol::object& varValue = customPair.second;
                        component[varName] = varValue;
                    }
                }
            }
        }
        m_eventManager.emit("EntityCreated", m_lua.create_table_with("entity", &entity));
        return entity;
    }
    else
    {
        std::puts(std::string("Entity" + entityName + "hasn't been registered. Returning nill entity").c_str());
        return m_nullEntity;
    }
}

Entity& EntityManager::createEntity(sol::table componentTable)
{
    auto& e = generateEntity();
    for(std::pair<sol::object, sol::table> pair : componentTable)
    {
        std::string componentName = pair.first.as<std::string>();
        e.addComponent(componentName, pair.second);
    }
    m_eventManager.emit("EntityCreated", m_lua.create_table_with("entity", &e));
    return e;
}

Entity& EntityManager::generateEntity()
{
    const auto id = m_uniqueID++;
    auto inserted = m_entities.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(id),
                                       std::forward_as_tuple(this, &m_eventManager, id));
    return inserted.first->second;
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
