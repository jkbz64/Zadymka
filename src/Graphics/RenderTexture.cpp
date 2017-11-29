#include <Graphics/RenderTexture.hpp>
#include <Graphics/Rectangle.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Text.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace
{
    template <typename T>
    constexpr float normalize(T value)
    {
      return value < 0 ? 0 : static_cast<float>(value) / 255.f;
    }
}

void RenderTexture::registerClass()
{
    Lua::getState().new_usertype<RenderTexture>("RenderTexture",
                                                sol::constructors<RenderTexture()>(),
                                                "create", &RenderTexture::create,
                                                "getTexture", &RenderTexture::getTexture,
                                                "drawRect", &RenderTexture::drawRect,
                                                "drawSprite", &RenderTexture::drawSprite,
                                                "drawText", &RenderTexture::drawText,
                                                "clear", &RenderTexture::clear,
                                                "display", &RenderTexture::display
    );
}

void RenderTexture::create(unsigned int w, unsigned int h)
{
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glGenTextures(1, m_texture.m_ID.get());
    m_texture.m_fboAttachment = true;
    glBindTexture(GL_TEXTURE_2D, m_texture.getID());
    m_texture.m_size = glm::vec2(w, h);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture.getID(), 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
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
