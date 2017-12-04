#ifndef INPUT_HPP
#define INPUT_HPP
#include <sol/state_view.hpp>

class GLFWwindow;

struct Input
{
    static sol::table createModule(sol::this_state);
private:
    friend class Window;
    static void setWindow(GLFWwindow*);
};

extern "C"
{
    struct lua_State;
}

extern "C" int luaopen_Zadymka_Input(lua_State*);

#endif