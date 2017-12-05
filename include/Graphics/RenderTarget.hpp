#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP
#include <Graphics/Camera.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Renderer.hpp>

class RenderTarget
{
public:
    RenderTarget();
    virtual ~RenderTarget() = default;
    virtual void clear(unsigned int, unsigned int, unsigned int, unsigned int = 255u) = 0;
    virtual void display() = 0;
    void draw(Drawable&, const Shader& = Shader());
    void setRenderer(Renderer*);

    void drawRect(float, float, int, int, int, int, int, int);
    void drawText(const std::string&, float, float, const std::string&, unsigned int);
    void drawSprite(const std::string&, float, float, int, int);

    const Camera& getCamera();
    void setCamera(const Camera&);
protected:
    std::unique_ptr<Renderer> m_renderer;
    Camera m_camera;
};

#endif
