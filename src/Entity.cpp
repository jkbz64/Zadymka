#include <Entity.hpp>
#include <Lua.hpp>
#include <EntityManager.hpp>

void Entity::registerClass()
{
    Lua::getState().new_usertype<Entity>("Entity",
                                         "new", sol::no_constructor,
                                         "getID", &Entity::getID,
                                         "addComponent", &Entity::addComponent,
                                         "get", [](Entity& e, const std::string& name) { return e.m_components[name]; },
                                         "getComponents", [](Entity& e) { return e.m_components; },
                                         "has", sol::overload(&Entity::hasComponent, &Entity::hasComponents),
                                         "components", &Entity::m_components
    );
    Lua::getState().script_file("entities/Entity.lua");
}

Entity::Entity(EntityManager* manager, int id) :
    m_manager(manager),
    m_id(id)
{

}

int Entity::getID()
{
    return m_id;
}

void Entity::addComponent(const std::string& componentName, sol::table table)
{
    m_components[componentName] = m_manager->createComponent(*this, componentName, table);
}

bool Entity::hasComponent(const std::string& name)
{
    return m_components.find(name) != std::end(m_components);
}

bool Entity::hasComponents(const std::vector<std::string>& names)
{
    bool has = true;
    if(!names.empty())
    {
        for(const auto& name : names)
            has = has && hasComponent(name);
    }
    return has;
}
