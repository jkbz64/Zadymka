#include <Graphics/Text.hpp>
#include <Graphics/Glyph.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/Renderer.hpp>

Text::Text() :
    Drawable()
{
    setColor(Color::Black);
    setCharacterSize(48);
}

Text::Text(Font &font) :
    Text()
{
    m_font = &font;
}

const std::string& Text::string() const
{
    return m_text;
}

const glm::vec2& Text::position() const
{
    return m_translation;
}

unsigned int Text::characterSize() const
{
    return m_characterSize;
}

const Color& Text::color() const
{
    return m_color;
}

Font* Text::font() const
{
    return m_font;
}

void Text::setPosition(const glm::vec2& pos)
{
    translate(glm::vec2(pos.x, pos.y));
}

void Text::setString(const std::string& str)
{
    m_text = str;
}

void Text::setColor(const Color& color)
{
    m_color = color;
}

void Text::setFont(Font *font)
{
    m_font = font;
}

void Text::setCharacterSize(unsigned int charSize)
{
    m_characterSize = charSize;
    scale(1.f, static_cast<float>(m_characterSize) / 48.f);
}

void Text::draw(Renderer *renderer)
{
    renderer->render(*this);
}