#ifndef TEXT_HPP
#define TEXT_HPP
#include <Graphics/Drawable.hpp>
#include <freetype2/ft2build.h>

class Font;

class Text : public Drawable, public Transformable
{
public:
    static void registerClass(sol::table);
    Text();
    Text(Font&);
    Text(const Text&) = default;
    Text(Text&&) = default;
    Text& operator=(const Text&) = default;
    Text& operator=(Text&&) = default;
    ~Text() = default;
    void setFont(Font*);
    void setString(const std::string&);
    void setPosition(const glm::vec2&);
    void setCharacterSize(unsigned int);
    const std::string& getString();
    const glm::vec2& getPosition();
    unsigned int getCharacterSize();
    void setColor(const Color&);
    const Color& getColor();
protected:
    virtual void draw(const Shader&) override;
    virtual Shader& getDefaultShader() override;
    Font* m_font;
    unsigned int m_characterSize;
    std::string m_text;
};

#endif
