#ifndef ZADYMKA_ZADYMKA_HPP
#define ZADYMKA_ZADYMKA_HPP
#include <sol/table.hpp>

namespace Zadymka
{
    sol::table createModule(sol::this_state);
    void init(sol::this_state);
    void deinit(sol::this_state);
}

extern "C"
{
    struct lua_State;
}

extern "C" int luaopen_Zadymka(lua_State* L);

#endif //ZADYMKA_ZADYMKA_HPP
