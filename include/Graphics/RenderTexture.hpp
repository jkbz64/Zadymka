#ifndef RENDERTEXTURE_HPP
#define RENDERTEXTURE_HPP
#include <Graphics/RenderTarget.hpp>
#include <Graphics/Texture.hpp>

class RenderTexture : public RenderTarget
{
public:
    RenderTexture() = default;
    RenderTexture(const RenderTexture&) = delete;
    RenderTexture(RenderTexture&&) = delete;
    RenderTexture& operator=(const RenderTexture&) = delete;
    RenderTexture& operator=(RenderTexture&&) = delete;
    ~RenderTexture() = default;
    void create(unsigned int w, unsigned int h);
    virtual void display() override;
    virtual void clear(unsigned int, unsigned int, unsigned int, unsigned int) override;
    Texture& getTexture();
private:
    Texture m_texture;
    unsigned int m_framebuffer;
};

#endif
