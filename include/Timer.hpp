#ifndef TIMER_HPP
#define TIMER_HPP
#include <sol/table.hpp>

struct Timer
{
    static sol::table createModule(sol::this_state);
};

extern "C"
{
    struct lua_State;
}

extern "C" int luaopen_Zadymka_Timer(lua_State*);

#endif