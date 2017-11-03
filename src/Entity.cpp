#include <Entity.hpp>
#include <Lua.hpp>
#include <EntityManager.hpp>

void Entity::registerClass()
{
    Lua::getState().new_usertype<Entity>("Entity",
                                         "new", sol::no_constructor,
                                         "getID", &Entity::getID,
                                         "getName", &Entity::getName,
                                         "addComponent", &Entity::addComponent,
                                         "getComponents", [](Entity& e) { return e.m_components; }
    );
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

std::string Entity::getName()
{
    return m_name;
}

void Entity::addComponent(const std::string& componentName, sol::variadic_args args)
{
    m_components[componentName] = m_manager->createComponent(*this, componentName, args);
}
