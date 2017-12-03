#include <Timer.hpp>
#include <sol/state_view.hpp>
#include <GLFW/glfw3.h>
#include <thread>

sol::table Timer::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module["getTime"] = []() { return glfwGetTime(); };
    module["sleep"] = [](int msec) { std::this_thread::sleep_for(std::chrono::milliseconds(msec)); };
    return module;
}


extern "C" int luaopen_Zadymka_Timer(lua_State* L)
{
    return sol::stack::call_lua(L, 1, Timer::createModule);
}