#include <Entity.hpp>
#include <Lua.hpp>

void Entity::registerClass()
{
    Lua::getState().new_usertype<Entity>("Entity",
                                         "new", sol::no_constructor,
                                         "getID", &Entity::getID
                                         );
}

Entity::Entity(int id) :
    m_id(id)
{

}

int Entity::getID()
{
    return m_id;
}
