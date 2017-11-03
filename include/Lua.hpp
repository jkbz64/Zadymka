#ifndef LUA_HPP
#define LUA_HPP
#include <sol/state.hpp>

struct Lua
{
    static sol::state& getState()
    {
        static sol::state state = sol::state();
        return state;
    }
};


#endif
