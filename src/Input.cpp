#include <Input.hpp>
#include <GLFW/glfw3.h>

namespace
{
    GLFWwindow* window{nullptr};
}

void Input::setWindow(GLFWwindow *w)
{
    window = w;
}

sol::table Input::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module["Mouse"] = lua.create_table_with(
            "isButtonPressed", [](int key) -> bool
            {
                int state = glfwGetMouseButton(window, key);
                return state == GLFW_PRESS;
            },
            "isButtonReleased", [](int key) -> bool
            {
                int state = glfwGetMouseButton(window, key);
                return state == GLFW_RELEASE;
            }
    );
    
    module["Keyboard"] = lua.create_table_with(
            "isKeyPressed", [](int key) -> bool
            {
                int state = glfwGetKey(window, key);
                return state == GLFW_PRESS;
            },
            "isButtonReleased", [](int key) -> bool
            {
                int state = glfwGetKey(window, key);
                return state == GLFW_RELEASE;
            }
    );
    return module;
}

extern "C" int luaopen_Zadymka_Input(lua_State* L)
{
    return sol::stack::call_lua(L, 1, Input::createModule);
}