#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <string>
#include <sol/table.hpp>

class EntityManager;

class Entity
{
public:
    Entity(EntityManager*, unsigned int);
    Entity(const Entity&) = delete;
    Entity(Entity&&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&) = delete;
    ~Entity() = default;
    void addComponent(const std::string&, sol::table);
    bool hasComponent(const std::string&);
    bool hasComponents(const std::vector<std::string>&);
private:
    friend class ECS;
    friend class EntityManager;
    EntityManager* m_manager;
    unsigned int m_id;
    std::unordered_map<std::string, sol::object> m_components;
};

#endif
