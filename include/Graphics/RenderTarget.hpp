#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP
#include <Graphics/Camera.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Graphics/Drawable.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Rectangle.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/Font.hpp>
#include <iostream>
#include <unordered_map>
#include <string>

template<class T>
class RenderTarget
{
public:
    RenderTarget<T>();
    virtual ~RenderTarget<T>() = default;
    void drawRect(float, float, int, int, int, int, int, int);
    void drawText(const std::string&, float, float, const std::string&, unsigned int);
    void drawSprite(const std::string&, float, float, int, int);

    virtual void display() = 0;
protected:
    Camera m_camera;
    struct RenderCache
    {
        GLuint m_cameraUBO;
        bool m_viewChanged;
    } m_renderCache;
};

template<class T>
RenderTarget<T>::RenderTarget() :
    m_renderCache({0, false})
{

}

template<class T>
inline void RenderTarget<T>::drawRect(float x, float y, int w, int h, int r, int g, int b, int a)
{
    Rectangle rect(w, h);
    rect.setPosition(glm::vec2(x, y));
    rect.setColor({r, g, b, a});
    static_cast<T&>(*this).draw(rect);
}

template<class T>
inline void RenderTarget<T>::drawSprite(const std::string& textureName, float x, float y, int w, int h)
{
    static std::unordered_map<std::string, Texture> cachedTextures;
    if(cachedTextures.find(textureName) == std::end(cachedTextures))
    {
        auto& texture = cachedTextures[textureName];
        if(!texture.loadFromFile("textures/" + textureName))
        {
            cachedTextures.erase(cachedTextures.find(textureName));
            std::cerr << "Failed to load texture " << textureName << '\n';
            return;
        }
    }
    Texture texture = cachedTextures[textureName];
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(glm::vec2(x, y));
    sprite.setSize(glm::vec2(w, h));
    static_cast<T&>(*this).draw(sprite);
}

template<class T>
inline void RenderTarget<T>::drawText(const std::string& str, float x, float y, const std::string& fontName, unsigned int charSize)
{
    static std::unordered_map<std::string, Font> cachedFonts;
    if(cachedFonts.find(fontName) == std::end(cachedFonts))
    {
        auto& font = cachedFonts[fontName];
        if(!font.loadFromFile("fonts/" + fontName))
        {
            cachedFonts.erase(cachedFonts.find(fontName));
            std::cerr << "Failed to load font " + fontName << '\n';
            return;
        }
    }
    Font& font = cachedFonts[fontName];
    Text text;
    text.setFont(&font);
    text.setPosition(glm::vec2(x, y));
    text.setString(str);
    text.setCharacterSize(charSize);
    static_cast<T&>(*this).draw(text);
}

#endif
