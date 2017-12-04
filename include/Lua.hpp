#ifndef LUA_HPP
#define LUA_HPP

#include <sol/state_view.hpp>

struct Lua
{
    static sol::state_view getState();
    template<typename... Args>
    static sol::protected_function_result scriptArgs(const std::string& code, Args&&... arguments)
    {
        sol::protected_function f = Lua::getState().script("return function(...) local arg = {...} " + code + " end");
        return f.call(arguments...);
    }
private:
    friend class Zadymka;
    static void setState(lua_State*);
};

#endif