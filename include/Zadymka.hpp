#ifndef ZADYMKA_HPP
#define ZADYMKA_HPP
#include <sol/forward.hpp>

struct Zadymka
{
    static sol::table createModule(sol::this_state);
    static bool init(sol::this_state);
    static void deinit(sol::this_state);
};

extern "C"
{
    struct lua_State;
}

extern "C" int luaopen_Zadymka(lua_State* L);

#endif
