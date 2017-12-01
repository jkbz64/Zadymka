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
    void init(EventManager&, EntityManager&) const;
    void update(double) const;
    void fixedUpdate(double) const;
    void draw(Window&, double) const;
protected:
    sol::object m_system;
    std::function<void(EventManager&, EntityManager&)> m_init;
    std::function<void(double)> m_update;
    std::function<void(double)> m_fixedUpdate;
    std::function<void(Window&, double)> m_draw;
};

#endif
