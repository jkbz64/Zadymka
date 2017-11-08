#ifndef LUASYSTEM_HPP
#define LUASYSTEM_HPP
#include <System.hpp>
#include <Lua.hpp>
#include <functional>

class LuaSystem : public System
{
public:
    static void registerClass();
    LuaSystem(const std::string&, sol::object);
    virtual ~LuaSystem() = default;
    virtual void initialize(SystemManager&) override;
    virtual void update(float) override;
    virtual void fixedUpdate(float) override;
    virtual void draw(Window&, float) override;
    sol::object getLuaSystem() const;
protected:
    sol::table m_systemTable;
    std::function<void(SystemManager&)> m_initialize;
    std::function<void(float)> m_update;
    std::function<void(float)> m_fixedUpdate;
    std::function<void(Window&, float)> m_draw;
    std::vector<std::string> m_requiredComponents;
};

#endif
