#ifndef DEFAULTRENDERER_HPP
#define DEFAULTRENDERER_HPP
#include <Graphics/Renderer.hpp>
#include <Graphics/Camera.hpp>

class Drawable;

class DefaultRenderer : public Renderer
{
public:
    DefaultRenderer(Camera& camera);
    virtual ~DefaultRenderer() = default;
    void render(Rectangle&) override;
    void render(Sprite&) override;
    void render(Text&) override;
    void render(VertexArray&) override;
private:
    Camera& m_camera;
};

#endif
