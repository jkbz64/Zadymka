#ifndef RENDERTEXTURE_HPP
#define RENDERTEXTURE_HPP
#include <Graphics/RenderTarget.hpp>
#include <Graphics/Texture.hpp>

class RenderTexture : public RenderTarget
{
public:
    static void registerClass();
    RenderTexture() = default;
    virtual ~RenderTexture() = default;
    void create(unsigned int w, unsigned int h);
    virtual void display() override;
    virtual void clear(unsigned int, unsigned int, unsigned int, unsigned int) override;

    Texture& getTexture();
private:
    Texture m_texture;
    GLuint m_framebuffer;
};

#endif
