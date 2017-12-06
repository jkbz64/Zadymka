#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include <sol/table.hpp>

struct Graphics
{
    static sol::table createModule(sol::this_state);
    static bool init(sol::this_state);
    static void deinit();
};

extern "C"
{
    struct lua_State;
}

extern "C" int luaopen_Zadymka_Graphics(lua_State*);

#endif
