#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <sol/state_view.hpp>
#include <sol/table.hpp>

class Window;
class EventManager;

class System
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
protected:
    sol::state_view m_lua;
    friend class ECS;
    sol::table m_systemTable;
};

#endif
