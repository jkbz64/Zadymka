#include <InputManager.hpp>

InputManager::Mouse::Mouse()
{
    m_onButtonPress = Lua::getState().script("return function() end");
    m_onButtonRelease = Lua::getState().script("return function() end");
    m_onMouseMove = Lua::getState().script("return function() end");
}

InputManager::Keyboard::Keyboard()
{
    m_onKeyPress = Lua::getState().script("return function() end");
    m_onKeyRelease = Lua::getState().script("return function() end");
}

InputManager::Mouse InputManager::m_mouse;
InputManager::Keyboard InputManager::m_keyboard;

void InputManager::registerClass()
{
    Lua::getState().new_usertype<Mouse>("Mouse",
                                        "new", sol::no_constructor,
                                        "isButtonPressed", [](Mouse& mouse, int key)
                                        {
                                            return mouse.isButtonPressed(static_cast<sf::Mouse::Button>(key));
                                        },
                                        "onButtonPress", &Mouse::m_onButtonPress,
                                        "onButtonRelease", &Mouse::m_onButtonRelease,
                                        "onMouseMove", &Mouse::m_onMouseMove
    );

    Lua::getState().new_usertype<Keyboard>("Keyboard",
                                        "new", sol::no_constructor,
                                        "isKeyPressed", [](Keyboard& keyboard, int key)
                                        {
                                            return keyboard.isKeyPressed(static_cast<sf::Keyboard::Key>(key));
                                        },
                                        "onKeyPress", &Keyboard::m_onKeyPress,
                                        "onKeyRelease", &Keyboard::m_onKeyRelease
    );

    Lua::getState().set("Mouse", &m_mouse);
    Lua::getState().set("Keyboard", &m_keyboard);
}


bool InputManager::Mouse::isButtonPressed(sf::Mouse::Button button)
{
    return sf::Mouse::isButtonPressed(button);
}

bool InputManager::Keyboard::isKeyPressed(sf::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}

void InputManager::update(const sf::Event &event)
{
    switch(event.type)
    {
        case sf::Event::MouseButtonPressed:
            m_mouse.m_onButtonPress.call(static_cast<int>(event.key.code));
        break;
        case sf::Event::MouseButtonReleased:
            m_mouse.m_onButtonRelease.call(static_cast<int>(event.key.code));
        break;
    case sf::Event::MouseMoved:
            m_mouse.m_onMouseMove.call(event.mouseMove.x, event.mouseMove.y);
        break;
    case sf::Event::KeyPressed:
            m_keyboard.m_onKeyPress.call(static_cast<int>(event.key.code));
        break;
    case sf::Event::KeyReleased:
            m_keyboard.m_onKeyRelease.call(static_cast<int>(event.key.code));
        break;
    default:
        break;
    }
}
