#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <string>
#include <sol/table.hpp>
#include <sol/object.hpp>

class EntityManager;

class Entity
{
public:
    static void registerClass(sol::table);
    Entity(EntityManager*, int);
    Entity(const Entity&) = delete;
    Entity(Entity&&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&) = delete;
    ~Entity() = default;
    int getID();
    void addComponent(const std::string&, sol::table);
    bool hasComponent(const std::string&);
    bool hasComponents(const std::vector<std::string>&);
private:
    friend class EntityManager;
    EntityManager* m_manager;
    int m_id;
    std::unordered_map<std::string, sol::object> m_components;
};

#endif
