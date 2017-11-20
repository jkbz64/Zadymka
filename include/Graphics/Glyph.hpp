#ifndef GLYPH_HPP
#define GLYPH_HPP
#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>

struct Glyph
{
    GLuint m_textureID;
    glm::ivec2 m_size;
    glm::ivec2 m_bearing;
    GLuint m_advance;
};

#endif
