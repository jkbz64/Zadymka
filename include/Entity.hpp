#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <string>
#include <sol/state.hpp>

class EntityManager;

class Entity
{
public:
    static void registerClass();
    Entity(EntityManager*, int);
    int getID();
    std::string getName();
    void addComponent(const std::string&, sol::variadic_args);
private:
    EntityManager* m_manager;
    int m_id;
    std::string m_name;
    std::unordered_map<std::string, sol::object> m_components;
};

#endif
