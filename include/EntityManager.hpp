#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <unordered_map>
#include <Lua.hpp>
#include <Entity.hpp>
#include <functional>

class EntityManager
{
public:
    static void registerClass();
    EntityManager();
    Entity& createEntity();
    Entity& getEntity(std::size_t);
    std::vector<std::reference_wrapper<Entity>> getEntities();
private:
    std::size_t m_poolIndex{0};
    Entity m_nullEntity;
    sol::object m_nullHandle;
    std::unordered_map<std::size_t, Entity> m_entities;

    sol::table m_handles;
    sol::table m_magicMetatable;
    sol::object createHandle(Entity&);

    friend class Entity;
    sol::object createComponent(Entity&, const std::string&, sol::variadic_args);
};

#endif
