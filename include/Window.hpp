#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <Scriptable.hpp>

class Window : public sf::RenderWindow, public Scriptable<Window>
{
public:
    static void exposeToLua();
    Window();
    virtual ~Window() = default;

    void close();

    void drawText(const std::string&, int x, int y, const std::string&, unsigned int);
protected:
    virtual void onCreate() override;
    virtual void onResize() override;

    sol::function m_onOpen;
    sol::function m_onResize;
    sol::function m_onClose;


    //Draw stuff
    std::unordered_map<std::string, sf::Font> m_cachedFonts;
};


#endif
