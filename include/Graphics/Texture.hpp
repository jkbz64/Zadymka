#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <Graphics/glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <string>
#include <memory>

class Texture
{
public:
    static void registerClass();
    Texture();
    Texture(const Texture&) = default;
    Texture& operator=(const Texture&) = default;
    Texture(Texture&&) = delete;
    Texture& operator=(Texture&&) = delete;
    ~Texture();
    GLuint getID() const;
    void bind() const;
    bool loadFromFile(const std::string&);
    const glm::vec2& getSize() const;
    bool isAttachment();
private:
    friend class Window;
    friend class RenderTexture;
    std::shared_ptr<GLuint> m_ID;
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
    //
    bool m_fboAttachment;
};

inline GLuint Texture::getID() const
{
    if(m_ID)
        return *m_ID.get();
    return 0;
}

inline void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, getID());
}

#endif
