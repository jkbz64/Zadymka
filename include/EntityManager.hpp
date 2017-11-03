#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <unordered_map>
#include <Lua.hpp>
#include <Entity.hpp>

class EntityManager
{
public:
    static void registerClass();
    EntityManager();
    Entity& createEntity();
private:
    std::size_t m_poolIndex{0};
    std::unordered_map<std::size_t, Entity> m_entities;

    sol::table m_handles;
    sol::table m_magicMetatable;
    sol::object createHandle(Entity&);
};

#endif
