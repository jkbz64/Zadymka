#ifndef FONT_HPP
#define FONT_HPP
#include <Graphics/Glyph.hpp>
#include <map>
#include <string>

using GLchar = char;

class Font
{
public:
    Font();
    Font(const std::string&);
    Font(const Font&) = delete;
    Font(Font&&) = delete;
    Font& operator=(const Font&) = delete;
    Font& operator=(Font&&) = delete;
    ~Font();
    bool loadFromFile(const std::string&);
    const Glyph& getGlyph(GLchar);
private:
    void* m_ft;
    void* m_face;
    GLuint m_id;
    std::map<GLchar, Glyph> m_glyphs;
};

#endif
