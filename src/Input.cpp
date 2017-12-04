#include <Input.hpp>
#include <GLFW/glfw3.h>
#include <Lua.hpp>

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
    sol::table buttons = Lua::getState().create_table_with(
            "Left", GLFW_MOUSE_BUTTON_LEFT,
            "Right", GLFW_MOUSE_BUTTON_RIGHT,
            "Middle", GLFW_MOUSE_BUTTON_MIDDLE,
            4, GLFW_MOUSE_BUTTON_4,
            5, GLFW_MOUSE_BUTTON_5,
            6, GLFW_MOUSE_BUTTON_6,
            7, GLFW_MOUSE_BUTTON_7,
            8, GLFW_MOUSE_BUTTON_8,
            "Last", GLFW_MOUSE_BUTTON_LAST
    );
    module["Mouse"] = lua.create_table_with(
            "Buttons", buttons,
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
    sol::table keys = lua.create_table();
    keys["UNKNOWN"] = GLFW_KEY_UNKNOWN;
    keys["SPACE"] = GLFW_KEY_SPACE;
    keys["APOSTROPHE"] = GLFW_KEY_APOSTROPHE;
    keys["COMMA"] = GLFW_KEY_COMMA;
    keys["MINUS"] = GLFW_KEY_MINUS;
    keys["PERIOD"] = GLFW_KEY_PERIOD;
    keys["SLASH"] = GLFW_KEY_SLASH;
    keys["K0"] = GLFW_KEY_0;
    keys["K1"] = GLFW_KEY_1;
    keys["K2"] = GLFW_KEY_2;
    keys["K3"] = GLFW_KEY_3;
    keys["K4"] = GLFW_KEY_4;
    keys["K5"] = GLFW_KEY_5;
    keys["K6"] = GLFW_KEY_6;
    keys["K7"] = GLFW_KEY_7;
    keys["K8"] = GLFW_KEY_8;
    keys["K9"] = GLFW_KEY_9;
    keys["SEMICOLON"] = GLFW_KEY_SEMICOLON;
    keys["EQUAL"] = GLFW_KEY_EQUAL;
    keys["A"] = GLFW_KEY_A;
    keys["B"] = GLFW_KEY_B;
    keys["C"] = GLFW_KEY_C;
    keys["D"] = GLFW_KEY_D;
    keys["E"] = GLFW_KEY_E;
    keys["F"] = GLFW_KEY_F;
    keys["G"] = GLFW_KEY_G;
    keys["H"] = GLFW_KEY_H;
    keys["I"] = GLFW_KEY_I;
    keys["J"] = GLFW_KEY_J;
    keys["K"] = GLFW_KEY_K;
    keys["L"] = GLFW_KEY_L;
    keys["M"] = GLFW_KEY_M;
    keys["N"] = GLFW_KEY_N;
    keys["O"] = GLFW_KEY_O;
    keys["P"] = GLFW_KEY_P;
    keys["Q"] = GLFW_KEY_Q;
    keys["R"] = GLFW_KEY_R;
    keys["S"] = GLFW_KEY_S;
    keys["T"] = GLFW_KEY_T;
    keys["U"] = GLFW_KEY_U;
    keys["V"] = GLFW_KEY_V;
    keys["W"] = GLFW_KEY_W;
    keys["X"] = GLFW_KEY_X;
    keys["Y"] = GLFW_KEY_Y;
    keys["Z"] = GLFW_KEY_Z;
    keys["LEFT_BRACKET"] = GLFW_KEY_LEFT_BRACKET;
    keys["BACKSLASH"] = GLFW_KEY_BACKSLASH;
    keys["RIGHT_BRACKET"] = GLFW_KEY_RIGHT_BRACKET;
    keys["GRAVE_ACCENT"] = GLFW_KEY_GRAVE_ACCENT;
    keys["WORLD_1"] = GLFW_KEY_WORLD_1;
    keys["WORLD_2"] = GLFW_KEY_WORLD_2;
    keys["ESCAPE"] = GLFW_KEY_ESCAPE;
    keys["ENTER"] = GLFW_KEY_ENTER;
    keys["TAB"] = GLFW_KEY_TAB;
    keys["BACKSPACE"] = GLFW_KEY_BACKSPACE;
    keys["INSERT"] = GLFW_KEY_INSERT;
    keys["DELETE"] = GLFW_KEY_DELETE;
    keys["RIGHT"] = GLFW_KEY_RIGHT;
    keys["LEFT"] = GLFW_KEY_LEFT;
    keys["DOWN"] = GLFW_KEY_DOWN;
    keys["UP"] = GLFW_KEY_UP;
    keys["PAGE_UP"] = GLFW_KEY_PAGE_UP;
    keys["PAGE_DOWN"] = GLFW_KEY_PAGE_DOWN;
    keys["HOME"] = GLFW_KEY_HOME;
    keys["END"] = GLFW_KEY_END;
    keys["CAPS_LOCK"] = GLFW_KEY_CAPS_LOCK;
    keys["SCROLL_LOCK"] = GLFW_KEY_SCROLL_LOCK;
    keys["NUM_LOCK"] = GLFW_KEY_NUM_LOCK;
    keys["PRINT_SCREEN"] = GLFW_KEY_PRINT_SCREEN;
    keys["PAUSE"] = GLFW_KEY_PAUSE;
    keys["F1"] = GLFW_KEY_F1;
    keys["F2"] = GLFW_KEY_F2;
    keys["F3"] = GLFW_KEY_F3;
    keys["F4"] = GLFW_KEY_F4;
    keys["F5"] = GLFW_KEY_F5;
    keys["F6"] = GLFW_KEY_F6;
    keys["F7"] = GLFW_KEY_F7;
    keys["F8"] = GLFW_KEY_F8;
    keys["F9"] = GLFW_KEY_F9;
    keys["F10"] = GLFW_KEY_F10;
    keys["F11"] = GLFW_KEY_F11;
    keys["F12"] = GLFW_KEY_F12;
    keys["F13"] = GLFW_KEY_F13;
    keys["F14"] = GLFW_KEY_F14;
    keys["F15"] = GLFW_KEY_F15;
    keys["F16"] = GLFW_KEY_F16;
    keys["F17"] = GLFW_KEY_F17;
    keys["F18"] = GLFW_KEY_F18;
    keys["F19"] = GLFW_KEY_F19;
    keys["F20"] = GLFW_KEY_F20;
    keys["F21"] = GLFW_KEY_F21;
    keys["F22"] = GLFW_KEY_F22;
    keys["F23"] = GLFW_KEY_F23;
    keys["F24"] = GLFW_KEY_F24;
    keys["F25"] = GLFW_KEY_F25;
    keys["KP_0"] = GLFW_KEY_KP_0;
    keys["KP_1"] = GLFW_KEY_KP_1;
    keys["KP_2"] = GLFW_KEY_KP_2;
    keys["KP_3"] = GLFW_KEY_KP_3;
    keys["KP_4"] = GLFW_KEY_KP_4;
    keys["KP_5"] = GLFW_KEY_KP_5;
    keys["KP_6"] = GLFW_KEY_KP_6;
    keys["KP_7"] = GLFW_KEY_KP_7;
    keys["KP_8"] = GLFW_KEY_KP_8;
    keys["KP_9"] = GLFW_KEY_KP_9;
    keys["KP_DECIMAL"] = GLFW_KEY_KP_DECIMAL;
    keys["KP_DIVIDE"] = GLFW_KEY_KP_DIVIDE;
    keys["KP_MULTIPLY"] = GLFW_KEY_KP_MULTIPLY;
    keys["KP_SUBTRACT"] = GLFW_KEY_KP_SUBTRACT;
    keys["KP_ADD"] = GLFW_KEY_KP_ADD;
    keys["KP_ENTER"] = GLFW_KEY_KP_ENTER;
    keys["KP_EQUAL"] = GLFW_KEY_KP_EQUAL;
    keys["LEFT_SHIFT"] = GLFW_KEY_LEFT_SHIFT;
    keys["LEFT_CONTROL"] = GLFW_KEY_LEFT_CONTROL;
    keys["LEFT_ALT"] = GLFW_KEY_LEFT_ALT;
    keys["LEFT_SUPER"] = GLFW_KEY_LEFT_SUPER;
    keys["RIGHT_SHIFT"] = GLFW_KEY_RIGHT_SHIFT;
    keys["RIGHT_CONTROL"] = GLFW_KEY_RIGHT_CONTROL;
    keys["RIGHT_ALT"] = GLFW_KEY_RIGHT_ALT;
    keys["RIGHT_SUPER"] = GLFW_KEY_RIGHT_SUPER;
    keys["MENU"] = GLFW_KEY_MENU;
    module["Keyboard"] = lua.create_table_with(
            "keys", keys,
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