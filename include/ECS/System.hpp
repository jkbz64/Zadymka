#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <ECS/Entity.hpp>

class Window;
class EventManager;

class System
{
public:
    static void registerClass();
    System();
    System(sol::object);
    System(const System&) = delete;
    System(System&&) = delete;
    System& operator=(const System&) = delete;
    System& operator=(System&&) = delete;
    ~System() = default;
    void init(EventManager&, EntityManager&);
    void update(float);
    void fixedUpdate(float);
    void draw(Window&, float);
    void onCreatedEntity(sol::table);
    void onDestroyedEntity(sol::table);
protected:
    sol::object m_system;
    std::string m_systemName;
    sol::function m_init;
    sol::function m_update;
    sol::function m_fixedUpdate;
    sol::function m_draw;
    std::vector<std::string> m_requiredComponents;
    std::unordered_map<int, sol::object> m_entities;
};

#endif
