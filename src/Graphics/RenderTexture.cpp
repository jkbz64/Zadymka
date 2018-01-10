#include <Graphics/RenderTexture.hpp>
#include <Graphics/Rectangle.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Renderer.hpp>
#include <Graphics/glad/glad.h>
#include <GLFW/glfw3.h>
#include <Graphics/DefaultRenderer.hpp>

namespace
{
    template <typename T>
    constexpr float normalize(T value)
    {
      return value < 0 ? 0 : static_cast<float>(value) / 255.f;
    }
}

RenderTexture::RenderTexture() :
        RenderTarget(new DefaultRenderer(m_camera)),
        m_framebuffer(0),
        m_oldViewport(0.f, 0.f, 800.f, 600.f)
{

}

RenderTexture::~RenderTexture()
{
    if(m_framebuffer != 0)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
        glDeleteFramebuffers(1, &m_framebuffer);
    }
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
    m_camera.setSize(glm::vec2(w, h));
    m_camera.setCenter(glm::vec2(w / 2.f, h / 2.f));
}

void RenderTexture::clear(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    m_oldViewport = glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]);
    glViewport(0, 0, m_texture.size().x, m_texture.size().y);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(normalize(r), normalize(g), normalize(b), normalize(a));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderTexture::display()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(m_oldViewport.x, m_oldViewport.y, m_oldViewport.z, m_oldViewport.w);
}

Texture RenderTexture::texture() const
{
    return m_texture;
}

unsigned int RenderTexture::getID() const
{
    return m_framebuffer;
}