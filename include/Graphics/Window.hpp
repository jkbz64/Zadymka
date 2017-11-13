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
    void drawText(const std::string&, float, float, const std::string&, unsigned int);
    void drawSprite(float, float, int, int, const std::string&);
protected:
    virtual void onCreate() override;
    virtual void onResize() override;
    sol::function m_onOpen;
    sol::function m_onResize;
    sol::function m_onClose;
    //Draw stuff
    std::unordered_map<std::string, sf::Font> m_cachedFonts;
    std::unordered_map<std::string, sf::Texture> m_cachedTextures;
};


#endif
