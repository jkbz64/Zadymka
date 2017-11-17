#include <InputManager.hpp>

InputManager::InputManager(Window &window) :
    m_window(window)
{
    m_mouse = Lua::getState().create_table_with(
        "isButtonPressed", [this](int key) -> bool
        {
            int state = glfwGetMouseButton(m_window.getNativeWindow(), key);
            return state == GLFW_PRESS;
        },
        "isButtonReleased", [this](int key) -> bool
        {
            int state = glfwGetMouseButton(m_window.getNativeWindow(), key);
            return state == GLFW_RELEASE;
        }
    );

    m_keyboard = Lua::getState().create_table_with(
        "isKeyPressed", [this](int key) -> bool
        {
            int state = glfwGetKey(m_window.getNativeWindow(), key);
            return state == GLFW_PRESS;
        },
        "isButtonReleased", [this](int key) -> bool
        {
            int state = glfwGetKey(m_window.getNativeWindow(), key);
            return state == GLFW_RELEASE;
        }
    );
    Lua::getState().set("Mouse", m_mouse);
    Lua::getState().set("Keyboard", m_keyboard);
}
