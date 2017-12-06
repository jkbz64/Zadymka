#ifndef FONT_HPP
#define FONT_HPP
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <Graphics/Glyph.hpp>
#include <sol/table.hpp>
#include <map>
#include <string>

using GLchar = char;

class Font
{
public:
    static void registerClass(sol::table);
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
