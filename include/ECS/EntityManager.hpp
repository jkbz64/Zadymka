#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP
#include <ECS/EventManager.hpp>
#include <ECS/Entity.hpp>
#include <unordered_map>
#include <functional>

class Entity;

class EntityManager
{
public:
    EntityManager(EventManager&);
    EntityManager(const EntityManager&) = delete;
    EntityManager(EntityManager&&) = delete;
    EntityManager& operator=(const EntityManager&) = delete;
    EntityManager& operator=(EntityManager&&) = delete;
    ~EntityManager();
    Entity& createEntity();
    Entity& createEntity(sol::table);
    void destroyEntity(std::size_t);
    Entity& getEntity(std::size_t);
    std::vector<std::reference_wrapper<Entity>> getEntities();
private:
    friend class ECS;
    EventManager& m_eventManager;
    std::size_t m_poolIndex{0};
    Entity m_nullEntity;
    sol::object m_nullHandle;
    std::unordered_map<std::size_t, Entity> m_entities;

    sol::table m_handles;
    sol::table m_magicMetatable;
    sol::object createHandle(Entity&);
protected:
    friend class Entity;
    sol::table getDefaultComponent(const std::string&);
};

#endif
