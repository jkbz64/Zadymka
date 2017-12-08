#include <Graphics/RenderTexture.hpp>
#include <Graphics/Rectangle.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Renderer.hpp>
#include <Graphics/glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{
    template <typename T>
    constexpr float normalize(T value)
    {
      return value < 0 ? 0 : static_cast<float>(value) / 255.f;
    }
}

RenderTexture::RenderTexture() :
        m_framebuffer(0)
{

}

void RenderTexture::create(unsigned int w, unsigned int h)
{
    if(m_framebuffer != 0)
        glDeleteFramebuffers(1, &m_framebuffer);
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    m_texture.create(w, h);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture.getID(), 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error("Framebuffer not completed");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTexture::clear(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glClearColor(normalize(r), normalize(g), normalize(b), normalize(a));
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderTexture::display()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Texture& RenderTexture::getTexture()
{
    return m_texture;
}
