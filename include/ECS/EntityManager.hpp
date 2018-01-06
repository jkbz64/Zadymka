#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP
#include <ECS/EventManager.hpp>
#include <ECS/Entity.hpp>
#include <sol/state_view.hpp>
#include <unordered_map>
#include <functional>

class Entity;

class EntityManager
{
public:
    static void registerEntity(const std::string&, sol::table);
    static void registerComponent(const std::string&, sol::table);
    EntityManager(sol::this_state, EventManager&);
    EntityManager(const EntityManager&) = delete;
    EntityManager(EntityManager&&) = delete;
    EntityManager& operator=(const EntityManager&) = delete;
    EntityManager& operator=(EntityManager&&) = delete;
    ~EntityManager();
    Entity& createEntity(const std::string&);
    Entity& createEntity(const std::string&, sol::table = sol::table());
    Entity& createEntity(sol::table = sol::table());
    void destroyEntity(std::size_t);
    Entity& getEntity(std::size_t);
private:
    sol::state_view m_lua;
    friend class ECS;
    EventManager& m_eventManager;
    std::size_t m_uniqueID{0};
    Entity m_nullEntity;
    Entity& generateEntity();
    std::unordered_map<std::size_t, Entity> m_entities;
    static std::unordered_map<std::string, sol::table> m_registeredComponents;
    static std::unordered_map<std::string, sol::table> m_registeredEntities;
protected:
    friend class Entity;
    sol::table getDefaultComponent(const std::string&);
};

#endif
