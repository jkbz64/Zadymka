#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <sol/table.hpp>

class Window;
class EventManager;

class System
{
public:
    System();
    System(sol::table);
    System(const System&) = delete;
    System(System&&) = default;
    System& operator=(const System&) = delete;
    System& operator=(System&&) = default;
    ~System() = default;
    sol::function init;
protected:
    friend class ECS;
    sol::table m_systemTable;
};

#endif
