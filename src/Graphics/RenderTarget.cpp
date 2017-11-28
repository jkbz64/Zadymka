#include <Graphics/RenderTarget.hpp>
#include <Graphics/Rectangle.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/Text.hpp>
#include <unordered_map>
#include <iostream>

void RenderTarget::draw(Drawable &drawable, const Shader &shader)
{
    std::reference_wrapper<const Shader> currentShader(shader);
    //Bind default shader in case shader was not given
    if(!currentShader.get().isLoaded())
        currentShader = drawable.getDefaultShader();
    currentShader.get().use();
    currentShader.get().setMatrix4("projection", m_camera.getProjection());
    currentShader.get().setMatrix4("view", m_camera.getView());
    drawable.draw(currentShader.get());
}

void RenderTarget::drawRect(float x, float y, int w, int h, int r, int g, int b, int a)
{
    Rectangle rect(w, h);
    rect.setPosition(glm::vec2(x, y));
    rect.setColor({r, g, b, a});
    draw(rect);
}

void RenderTarget::drawSprite(const std::string& textureName, float x, float y, int w, int h)
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
    draw(sprite);
}

void RenderTarget::drawText(const std::string& str, float x, float y, const std::string& fontName, unsigned int charSize)
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
    draw(text);
}

void RenderTarget::setCamera(const Camera& camera)
{
    m_camera = camera;
}

const Camera& RenderTarget::getCamera()
{
    return m_camera;
}
