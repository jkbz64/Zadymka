#ifndef RENDERTEXTURE_HPP
#define RENDERTEXTURE_HPP
#include <Graphics/RenderTarget.hpp>
#include <Graphics/Texture.hpp>

class RenderTexture : public RenderTarget
{
public:
    RenderTexture();
    RenderTexture(const RenderTexture&) = delete;
    RenderTexture(RenderTexture&&) = delete;
    RenderTexture& operator=(const RenderTexture&) = delete;
    RenderTexture& operator=(RenderTexture&&) = delete;
    ~RenderTexture();
    void create(unsigned int w, unsigned int h);
    virtual void display() override;
    virtual void clear(unsigned int, unsigned int, unsigned int, unsigned int) override;
    Texture getTexture();
    unsigned int getID() const;
private:
    unsigned int m_framebuffer;
    Texture m_texture;
    int m_oldFramebuffer;
    glm::ivec4 m_oldViewport;
};

#endif
