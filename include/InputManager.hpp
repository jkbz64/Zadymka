#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP
#include <Lua.hpp>
#include <Graphics/Window.hpp>

class InputManager
{
public:
    static void registerClass();
    InputManager(Window&);
    InputManager(const InputManager&) = delete;
    InputManager(InputManager&&) = delete;
    InputManager& operator=(const InputManager&) = delete;
    InputManager& operator=(InputManager&&) = delete;
    ~InputManager() = default;
private:
    sol::table m_mouse;
    sol::table m_keyboard;
    Window& m_window;
};






#endif
