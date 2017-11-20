#ifndef FONT_HPP
#define FONT_HPP
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <GLFW/glfw3.h>
#include <string>
#include <Graphics/Glyph.hpp>
#include <map>

class Font
{
public:
    static void registerClass();
    Font();
    Font(const std::string&);
    ~Font() = default;
    bool loadFromFile(const std::string&);
    const Glyph& getGlyph(GLchar);
private:
    GLuint m_id;
    std::map<GLchar, Glyph> m_glyphs;
};

#endif
