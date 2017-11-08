#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <Lua.hpp>

class Window : public sf::RenderWindow
{
public:
    static void registerClass();
    Window();
    virtual ~Window() = default;

    void close();

    //Draw fncs
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
