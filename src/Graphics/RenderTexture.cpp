#include <Graphics/RenderTexture.hpp>
#include <Graphics/Rectangle.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Text.hpp>


void RenderTexture::registerClass()
{
    /*Lua::getState().new_usertype<RenderTexture>("RenderTexture",
                                                sol::constructors<RenderTexture()>(),
                                                "draw", sol::overload(&RenderTexture::draw<Rectangle>,
                                                                      &RenderTexture::draw<Sprite>,
                                                                      &RenderTexture::draw<Text>),
                                                "drawRect", &RenderTexture::drawRect,
                                                "drawSprite", &RenderTexture::drawSprite,
                                                "drawText", &RenderTexture::drawText
    );*/
}

/*void RenderTexture::initialize(unsigned int w, unsigned int h)
{
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

    glGenTextures(1, &m_texture.m_ID);
    glBindTexture(GL_TEXTURE_2D, m_texture.m_ID);
    m_texture.m_size.x = w;
    m_texture.m_size.y = h;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture.m_ID, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::logic_error("lul");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //Default RenderTexture camera UBO
    GLuint bindingPoint = 2;
    glGenBuffers(1, &m_renderCache.m_cameraUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, m_renderCache.m_cameraUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(m_camera.getView()));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(m_camera.getProjection()));
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, m_renderCache.m_cameraUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    m_initialized = true;
}*/

void RenderTexture::create(unsigned int w, unsigned int h)
{
   /* if(!m_initialized)
        initialize(w, h);*/
}

void RenderTexture::display()
{
    /*glBindTexture(GL_TEXTURE_2D, m_texture.m_ID);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, m_texture.m_size.x, m_texture.m_size.y);*/
}
