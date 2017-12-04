#ifndef INPUT_HPP
#define INPUT_HPP
#include <sol/state_view.hpp>

class GLFWwindow;

namespace Input
{
    void setWindow(GLFWwindow*);
    sol::table createModule(sol::this_state);
}

extern "C"
{
    struct lua_State;
}

extern "C" int luaopen_Zadymka_Input(lua_State*);

#endif