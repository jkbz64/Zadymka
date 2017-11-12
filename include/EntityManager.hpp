#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <unordered_map>
#include <Lua.hpp>
#include <Entity.hpp>
#include <functional>
#include <EventManager.hpp>

class EntityManager
{
public:
    static void registerClass();
    EntityManager(EventManager&);
    Entity& createEntity();
    Entity& createEntity(const std::string&);
    void destroyEntity(std::size_t);
    Entity& getEntity(std::size_t);
    std::vector<std::reference_wrapper<Entity>> getEntities();
private:
    EventManager& m_eventManager;
    std::size_t m_poolIndex{0};
    Entity m_nullEntity;
    sol::object m_nullHandle;
    std::unordered_map<std::size_t, Entity> m_entities;

    sol::table m_handles;
    sol::table m_magicMetatable;
    sol::object createHandle(Entity&);

    friend class Entity;
    sol::object createComponent(Entity&, const std::string&, sol::table);
};

#endif
