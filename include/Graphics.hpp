#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include <sol/table.hpp>

namespace Graphics
{
    sol::table createModule(sol::this_state);
    bool init();
    void deinit();
}

extern "C"
{
    struct lua_State;
}

extern "C" int luaopen_Zadymka_Graphics(lua_State*);

#endif
