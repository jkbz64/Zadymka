#include <Graphics/Font.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

Font::Font() :
    m_id(0)
{

}

Font::~Font()
{
    if(m_face)
        FT_Done_Face(static_cast<FT_Face>(m_face));
    if(m_ft)
        FT_Done_FreeType(static_cast<FT_Library>(m_ft));
    if(m_id != 0)
        glDeleteTextures(1, &m_id);
}

Font::Font(const std::string &fontName)
{
    loadFromFile(fontName);
}

bool Font::loadFromFile(const std::string &file)
{
    //Load library
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::puts("Could not init FreeType Library");
    m_ft = ft;
    //Load font face
    FT_Face face;
    if (FT_New_Face(static_cast<FT_Library>(m_ft), file.c_str(), 0, &face))
    {
       // std::cerr << "Failed to load font face " + file + '\n';
        return false;
    }
    m_face = face;
    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (GLubyte c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::puts("Failed to load character " + c);
            continue;
        }
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Glyph glyph = {
            m_id,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<GLuint>(face->glyph->advance.x)
        };
        m_glyphs.emplace(c, glyph);
    }
    return true;
}

const Glyph& Font::getGlyph(GLchar c)
{
    return m_glyphs[c];
}
