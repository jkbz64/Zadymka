#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <memory>
#include <string>
#include <glm/vec2.hpp>

using GLuint = unsigned int;

class Texture
{
public:
    Texture();
    Texture(const Texture&) = default;
    Texture& operator=(const Texture&) = default;
    Texture(Texture&&) = default;
    Texture& operator=(Texture&&) = default;
    ~Texture() = default;
    GLuint getID() const;
    const glm::uvec2& size() const;
    void bind() const;
    void create(unsigned int, unsigned int);
    bool loadFromFile(const std::string&);
    bool loadFromMemory(const std::string&);
    void setFilter(const GLuint&, const GLuint&);
    void setWrap(const GLuint&, const GLuint&);
    Texture subimage(const glm::ivec2&, const glm::uvec2&);
private:
    friend class Graphics;
    friend class Window;
    friend class RenderTexture;
    std::shared_ptr<GLuint> m_ID;
    glm::uvec2 m_size;
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
