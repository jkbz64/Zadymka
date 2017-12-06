#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP
#include <unordered_map>
#include <ECS/Entity.hpp>
#include <functional>
#include <ECS/EventManager.hpp>

class Entity;

class EntityManager
{
public:
    static void registerClass(sol::table);
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
