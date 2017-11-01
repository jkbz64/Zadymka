#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <Scriptable.hpp>

class Window : public sf::RenderWindow, public Scriptable<Window>
{
public:
    static void exposeToLua();
    Window();
    virtual ~Window() = default;

    void close();
protected:
    virtual void onCreate() override;
    virtual void onResize() override;
    sol::function m_onOpen;
    sol::function m_onResize;
    sol::function m_onClose;
};


#endif
