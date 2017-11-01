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
protected:
};


#endif
