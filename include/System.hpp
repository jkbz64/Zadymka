#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <Window.hpp>

class SystemManager;

class System
{
public:
    System(const std::string& systemName) :
        m_name(systemName)
    { }
    virtual ~System() = default;
    virtual void initialize(SystemManager&) = 0;
    virtual void update(float) = 0;
    virtual void fixedUpdate(float) = 0;
    virtual void draw(Window&, float) = 0;
    const std::string& getName() const;
    sol::object getLuaRef() const;
protected:
    std::string m_name;
    sol::object m_luaRef;
};

inline const std::string& System::getName() const
{
    return m_name;
}

inline sol::object System::getLuaRef() const
{
    return m_luaRef;
}

#endif
