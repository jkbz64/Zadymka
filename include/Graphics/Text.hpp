#ifndef TEXT_HPP
#define TEXT_HPP
#include <Graphics/Drawable.hpp>
#include <freetype2/ft2build.h>

class Font;

class Text : public Drawable<Text>
{
public:
    static void registerClass();
    Text();
    Text(Font&);
    void setFont(Font*);
    void setString(const std::string&);
    void setPosition(const glm::vec2&);
protected:
    virtual void draw(Window &) override;
    Font* m_font;
    std::string m_text;
};

#endif
