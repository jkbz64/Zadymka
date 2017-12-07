#include <Graphics/Text.hpp>
#include <Graphics/Glyph.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/Renderer.hpp>

void Text::registerClass(sol::table module)
{
    module.new_usertype<Text>("Text",
                                       sol::constructors<Text(), Text(Font&)>(),
                                       "setPosition", [](Text& text, float x, float y) { text.setPosition(glm::vec2(x, y)); },
                                       "getPosition", &Text::getPosition,
                                       "setString", &Text::setString,
                                       "getString", &Text::getString,
                                       "setFont", &Text::setFont,
                                       "setCharacterSize", &Text::setCharacterSize,
                                       "getCharacterSize", &Text::getCharacterSize,
                                       "setColor", &Text::setColor,
                                       "getColor", &Text::getColor,
                                       sol::base_classes, sol::bases<Drawable>()
                                       );
}

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

void Text::setFont(Font *font)
{
    m_font = font;
}

void Text::setString(const std::string& str)
{
    m_text = str;
}

const std::string& Text::getString() const
{
    return m_text;
}

void Text::setPosition(const glm::vec2& pos)
{
    translate(glm::vec2(pos.x, pos.y));
}

const glm::vec2& Text::getPosition() const
{
    return m_translation;
}

void Text::setCharacterSize(unsigned int charSize)
{
    m_characterSize = charSize;
    scale(1.f, static_cast<float>(m_characterSize) / 48.f);
}

unsigned int Text::getCharacterSize() const
{
    return m_characterSize;
}

const Color& Text::getColor() const
{
    return m_color;
}

void Text::setColor(const Color& color)
{
    m_color = color;
}

Font* Text::getFont() const
{
    return m_font;
}

void Text::draw(Renderer *renderer)
{
    renderer->render(*this);
}