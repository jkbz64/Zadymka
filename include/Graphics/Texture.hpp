#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <string>

class Texture
{
public:
    static void registerClass();
    Texture();
    void bind() const;
    bool loadFromFile(const std::string&);
    const glm::vec2& getSize();
private:
    GLuint m_ID;
    //Texture dimensions
    glm::vec2 m_size;
    //Format
    GLuint m_internalFormat;
    GLuint m_imageFormat;
    //Texture config
    GLuint m_wrapS;
    GLuint m_wrapT;
    GLuint m_filterMin;
    GLuint m_filterMax;
};

#endif
