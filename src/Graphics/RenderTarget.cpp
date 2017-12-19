#include <Graphics/RenderTarget.hpp>
#include <Graphics/Rectangle.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/DefaultRenderer.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/Text.hpp>
#include <unordered_map>

RenderTarget::RenderTarget(Renderer* renderer) :
    m_renderer(renderer)
{

}

RenderTarget::~RenderTarget() = default;

void RenderTarget::draw(Drawable& drawable)
{
    drawable.draw(m_renderer.get());
}

void RenderTarget::draw(Drawable& drawable, const Shader&)
{
    //TODO set custom renderer
    drawable.draw(m_renderer.get());
}

void RenderTarget::setRenderer(Renderer *renderer)
{
    m_renderer.reset(renderer);
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
        if(!texture.loadFromFile(textureName))
        {
            cachedTextures.erase(cachedTextures.find(textureName));
            std::puts(std::string("Failed to load texture " + textureName).c_str());
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

void RenderTarget::drawTexture(const Texture& texture, float x, float y)
{
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(glm::vec2(x, y));
    draw(sprite);
}

void RenderTarget::drawText(const std::string& str, float x, float y, const std::string& fontName, unsigned int charSize)
{
    static std::unordered_map<std::string, Font> cachedFonts;
    if(cachedFonts.find(fontName) == std::end(cachedFonts))
    {
        auto& font = cachedFonts[fontName];
        if(!font.loadFromFile(fontName))
        {
            cachedFonts.erase(cachedFonts.find(fontName));
            std::puts(std::string("Failed to load font " + fontName).c_str());
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
