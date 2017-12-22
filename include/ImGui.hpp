#ifndef IMGUI_HPP
#define IMGUI_HPP
#include <sol/forward.hpp>

struct GLFWwindow;

struct ImGUI
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
    
extern "C" int luaopen_Zadymka_ImGui(lua_State *);

#endif