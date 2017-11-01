#include <Window.hpp>

void Window::exposeToLua()
{
    Lua::getState().new_usertype<Window>("Window",
                             "new", sol::no_constructor,
                             "setTitle", [](Window& window, const std::string& title)
                             {
                                window.setTitle(sf::String(title));
                             },
                             "getSize", [](Window& window)
                             {
                                return std::make_tuple(window.getSize().x, window.getSize().y);
                             },
                             "setSize", [](Window& window, unsigned int w, unsigned int h)
                             {
                                window.setSize(sf::Vector2u(w, h));
                             },
                             "setFramerateLimit", &Window::setFramerateLimit,
                             "setVSync", &Window::setVerticalSyncEnabled
    );
}

Window::Window()  :
      sf::RenderWindow(),
      Scriptable<Window>()
{

}


