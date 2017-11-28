#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP
#include <Graphics/Camera.hpp>
#include <Graphics/Drawable.hpp>
#include <Graphics/Texture.hpp>

class RenderTarget
{
public:
    RenderTarget() = default;
    virtual ~RenderTarget() = default;
    virtual void clear(unsigned int, unsigned int, unsigned int, unsigned int = 255u) = 0;
    virtual void draw(Drawable&, const Shader& = Shader()) = 0;
    virtual void display() = 0;

    void drawRect(float, float, int, int, int, int, int, int);
    void drawText(const std::string&, float, float, const std::string&, unsigned int);
    void drawSprite(const std::string&, float, float, int, int);
};

#endif
