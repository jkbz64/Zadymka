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

    //xD
    Lua::getState().script(R"(
        Keys = {
            Unknown = -1,
            A = 0,
            B = 1,
            C = 2,
            D = 3,
            E = 4,
            F = 5,
            G = 6,
            H = 7,
            I = 8,
            J = 9,
            K = 10,
            L = 11,
            M = 12,
            N = 13,
            O = 14,
            P = 15,
            Q = 16,
            R = 17,
            S = 18,
            T = 19,
            U = 20,
            V = 21,
            W = 22,
            X = 23,
            Y = 24,
            Z = 25,
            Num0 = 26,
            Num1 = 27,
            Num2 = 28,
            Num3 = 29,
            Num4 = 30,
            Num5 = 31,
            Num6 = 32,
            Num7 = 33,
            Num8 = 34,
            Num9 = 35,
            Escape = 36,
            LControl = 37,
            LShift = 38,
            LAlt = 39,
            LSystem = 40,
            RControl = 41,
            RShift = 42,
            RAlt = 43,
            RSystem = 44,
            Menu = 45,
            LBracket = 46,
            RBracket = 47,
            SemiColon = 48,
            Comma = 49,
            Period = 50,
            Quote = 51,
            Slash = 52,
            BackSlash = 53,
            Tilde = 54,
            Equal = 55,
            Dash = 56,
            Space = 57,
            Return = 58,
            BackSpace = 59,
            Tab = 60,
            PageUp = 61,
            PageDown = 62,
            End = 63,
            Home = 64,
            Insert = 65,
            Delete = 66,
            Add = 67,
            Subtract = 68,
            Multiply = 69,
            Divide = 70,
            Left = 71,
            Right = 72,
            Up = 73,
            Down = 74,
            Numpad0 = 75,
            Numpad1 = 76,
            Numpad2 = 77,
            Numpad3 = 78,
            Numpad4 = 79,
            Numpad5 = 80,
            Numpad6 = 81,
            Numpad7 = 82,
            Numpad8 = 83,
            Numpad9 = 84,
            F1 = 85,
            F2 = 86,
            F3 = 87,
            F4 = 88,
            F5 = 89,
            F6 = 90,
            F7 = 91,
            F8 = 92,
            F9 = 93,
            F10 = 94,
            F11 = 95,
            F12 = 96,
            F13 = 97,
            F14 = 98,
            F15 = 99,
            Pause = 100,
            KeyCount = 111
        })");
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
