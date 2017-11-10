#include <Entity.hpp>
#include <Lua.hpp>
#include <EntityManager.hpp>

void Entity::registerClass()
{
    Lua::getState().new_usertype<Entity>("Entity",
                                         "new", sol::no_constructor,
                                         "getID", &Entity::getID,
                                         "getName", &Entity::getName,
                                         "setPosition", &Entity::setPosition,
                                         "move", &Entity::move,
                                         "getPosition", [](Entity& e)
                                         {
                                            return std::make_tuple(e.m_position.x, e.m_position.y);
                                         },
                                         "addComponent", &Entity::addComponent,
                                         "getComponents", [](Entity& e) { return e.m_components; },
                                         "has", sol::overload(&Entity::hasComponent, &Entity::hasComponents),
                                         "components", &Entity::m_components
    );
    Lua::getState().script_file("entities/Entity.lua");
}

Entity::Entity(EntityManager* manager, int id) :
    m_manager(manager),
    m_id(id),
    m_position(0, 0)
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

void Entity::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}

void Entity::move(float x, float y)
{
    m_position.x += x;
    m_position.y += y;
}

const sf::Vector2f& Entity::getPosition()
{
    return m_position;
}

const sf::Vector2f& Entity::getPreviousPosition()
{
    return m_previousPosition;
}

void Entity::addComponent(const std::string& componentName, sol::variadic_args args)
{
    m_components[componentName] = m_manager->createComponent(*this, componentName, args);
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
