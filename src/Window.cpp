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
                             "setVSync", &Window::setVerticalSyncEnabled,
                             "onOpen", &Window::m_onOpen,
                             "onResize", &Window::m_onResize,
                             "onClose", &Window::m_onClose
    );
}

Window::Window()  :
      sf::RenderWindow(),
      Scriptable<Window>()
{

}


void Window::close()
{
    if(m_onClose.valid())
        m_onClose.call();
    sf::RenderWindow::close();
}

void Window::onCreate()
{
    sf::RenderWindow::onCreate();
    if(m_onOpen.valid())
        m_onOpen.call();
}

void Window::onResize()
{
    sf::RenderWindow::onResize();
    if(m_onResize.valid())
        m_onResize.call();
}

