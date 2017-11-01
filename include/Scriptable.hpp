#ifndef SCRIPTABLE_HPP
#define SCRIPTABLE_HPP
#include <sol/state.hpp>

struct Lua
{
    static sol::state& getState()
    {
        static sol::state state = sol::state();
        return state;
    }
};

template<class T>
class Scriptable
{
public:
    Scriptable()
    {
        static bool exposed = false;
        if(!exposed)
        {
            T::exposeToLua();
            exposed = true;
        }
        m_luaRef = sol::make_object(Lua::getState(), static_cast<T*>(this));
    }
    virtual ~Scriptable() = default;
    sol::table getMetatable()
    {
        sol::userdata ud = m_luaRef;
        return ud[sol::metatable_key];
    }
    sol::object getLuaReference()
    {
        return m_luaRef;
    }
protected:
    sol::object m_luaRef;
};

#endif
