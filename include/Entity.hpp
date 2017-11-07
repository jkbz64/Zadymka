#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <string>
#include <sol/state.hpp>
#include <SFML/System.hpp>

class EntityManager;

class Entity
{
public:
    static void registerClass();
    Entity(EntityManager*, int);
    int getID();
    std::string getName();
    void setPosition(float, float);
    void move(float, float);
    const sf::Vector2f& getPosition();
    const sf::Vector2f& getPreviousPosition();
    void addComponent(const std::string&, sol::variadic_args);
private:
    friend class EntityManager;
    friend class RenderingSystem;
    EntityManager* m_manager;
    int m_id;
    std::string m_name;
    std::unordered_map<std::string, sol::object> m_components;
    sf::Vector2f m_position;
    sf::Vector2f m_previousPosition;
};

#endif
