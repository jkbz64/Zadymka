#ifndef LUA_HPP
#define LUA_HPP
#include <sol/state.hpp>
#include <string>

struct Lua
{
    static sol::state& getState()
    {
        static sol::state state = sol::state();
        return state;
    }

    template<typename... Args>
    static sol::protected_function_result scriptArgs(const std::string& code, Args&&... arguments)
    {
        sol::protected_function f = Lua::getState().script("return function(...) local arg = {...} " + code + " end");
        return f.call(arguments...);
    }
};


#endif
