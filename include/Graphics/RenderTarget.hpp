#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP
#include <Graphics/Camera.hpp>
#include <bits/unique_ptr.h>

class Drawable;
class Shader;
class Renderer;
class Texture;

class RenderTarget
{
public:
    RenderTarget(Renderer*);
    virtual ~RenderTarget();
    virtual void clear(unsigned int, unsigned int, unsigned int, unsigned int = 255u) = 0;
    virtual void display() = 0;
    void draw(Drawable&);
    void draw(Drawable&, const Shader&);
    void setRenderer(Renderer*);

    void drawRect(float, float, int, int, int, int, int, int);
    void drawText(const std::string&, float, float, const std::string&, unsigned int);
    void drawSprite(const std::string&, float, float, int, int);
    void drawTexture(const Texture&, float, float);
protected:
    friend class Graphics;
    std::unique_ptr<Renderer> m_renderer;
    Camera m_camera;
};

#endif
