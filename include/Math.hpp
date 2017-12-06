#ifndef MATH_HPP
#define MATH_HPP
#include <sol/table.hpp>

struct Math
{
    static sol::table createModule(sol::this_state);
};

extern "C" {
struct lua_State;
}

extern "C" int luaopen_Zadymka_Math(lua_State*);

#endif
