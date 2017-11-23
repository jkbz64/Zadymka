#ifndef RENDERTEXTURE_HPP
#define RENDERTEXTURE_HPP
#include <Graphics/RenderTarget.hpp>
#include <Graphics/Texture.hpp>

class RenderTexture : public RenderTarget<RenderTexture>
{
public:
    static void registerClass();
    RenderTexture() = default;
    virtual ~RenderTexture() = default;
    void create(unsigned int w, unsigned int h);

    template<class T>
    void draw(T&);

    virtual void display() override;
    Texture m_texture;
    GLuint m_framebuffer;
};

template<class T>
inline void RenderTexture::draw(T& drawable)
{
    Shader& shader = drawable.m_renderDetails.m_shader.use();
    GLuint blockIndex = glGetUniformBlockIndex(shader.getID(), "Camera");
    glUniformBlockBinding(shader.getID(), blockIndex, 2);
    drawable.m_renderDetails.m_cameraSet = false;
    static_cast<Drawable<T>&>(drawable).draw();
}

#endif
