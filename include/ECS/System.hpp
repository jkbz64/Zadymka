#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <ECS/Scriptable.hpp>

class Window;
class EventManager;

class System : public Scriptable<System>
{
public:
    System();
    System(sol::this_state);
    System(sol::this_state, sol::table);
    System(const System&) = delete;
    System(System&&) = default;
    System& operator=(const System&) = delete;
    System& operator=(System&&) = default;
    ~System() = default;
    sol::function init;
};

#endif
