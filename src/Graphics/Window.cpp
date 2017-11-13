#include <Graphics/Window.hpp>
#include <iostream>

void Window::registerClass()
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
                             "onClose", &Window::m_onClose,
                             //Draw
                             "drawText", &Window::drawText,
                             "drawRect", &Window::drawRect,
                             "drawSprite", &Window::drawSprite
    );
}

Window::Window()  :
      sf::RenderWindow()
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

void Window::drawText(const std::string& text, float x, float y, const std::string& fontName, unsigned int charSize)
{
    if(m_cachedFonts.find(fontName) == m_cachedFonts.end())
    {
        sf::Font& font = m_cachedFonts[fontName] = sf::Font();
        if(!font.loadFromFile("fonts/" + fontName))
        {
            m_cachedFonts.erase(fontName);
            return;
        }
    }
    sf::Font& font = m_cachedFonts[fontName];
    sf::Text drawText;
    drawText.setFont(font);
    drawText.setString(text);
    drawText.setCharacterSize(charSize);
    drawText.setPosition(x, y);
    sf::RenderWindow::draw(drawText);
}

void Window::drawSprite(float x, float y, int w, int h, const std::string &textureName)
{
    if(m_cachedTextures.find(textureName) == m_cachedTextures.end() && !textureName.empty())
    {
        sf::Texture& texture = m_cachedTextures[textureName] = sf::Texture();
        if(!texture.loadFromFile("textures/" + textureName))
        {
            m_cachedTextures.erase(textureName);
            return;
        }
    }

    sf::RectangleShape spriteShape(sf::Vector2f(w, h));
    sf::Texture& texture = m_cachedTextures[textureName];
    spriteShape.setTexture(&texture);
    spriteShape.setPosition(x, y);
    sf::RenderWindow::draw(spriteShape);
}

void Window::drawRect(float x, float y, int w, int h, int r = 255, int g = 255, int b = 255)
{
    sf::RectangleShape rect(sf::Vector2f(w, h));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color(r, g, b));
    sf::RenderWindow::draw(rect);
}
