#ifndef TEXT_HPP
#define TEXT_HPP
#include <Graphics/Drawable.hpp>
#include <Graphics/Transformable.hpp>
#include <Graphics/Color.hpp>
#include <string>

class Font;

class Text : public Drawable, public Transformable
{
public:
    Text();
    Text(Font&);
    Text(const Text&) = default;
    Text(Text&&) = default;
    Text& operator=(const Text&) = default;
    Text& operator=(Text&&) = default;
    ~Text() = default;
    
    const glm::vec2& position() const;
    const std::string& string() const;
    unsigned int characterSize() const;
    const Color& color() const;
    Font* font() const;
    
    void setFont(Font*);
    void setString(const std::string&);
    void setPosition(const glm::vec2&);
    void setCharacterSize(unsigned int);
    void setColor(const Color&);
protected:
    friend class Graphics;
    void draw(Renderer*) override;
    Font* m_font;
    Color m_color;
    unsigned int m_characterSize;
    std::string m_text;
};

#endif
