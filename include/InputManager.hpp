#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP
#include <Lua.hpp>
#include <SFML/Window.hpp>

class InputManager
{
public:
    static void registerClass();
    InputManager() = default;
    ~InputManager() = default;
    //void update(const sf::Event&);
private:
    struct Mouse
    {
        Mouse();
        bool isButtonPressed(sf::Mouse::Button);
        sol::function m_onButtonPress;
        sol::function m_onButtonRelease;
        sol::function m_onMouseMove;
    } static m_mouse;
    struct Keyboard
    {
        Keyboard();
        bool isKeyPressed(sf::Keyboard::Key);
        sol::function m_onKeyPress;
        sol::function m_onKeyRelease;
    } static m_keyboard;
};






#endif
