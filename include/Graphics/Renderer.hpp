#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <Graphics/Camera.hpp>

class Drawable;
class Rectangle;
class Sprite;
class Text;
class VertexArray;


class Renderer
{
public:
    Renderer(Camera& camera) :
            m_camera(camera) {}
    virtual ~Renderer() = default;
    virtual void render(Rectangle&) = 0;
    virtual void render(Sprite&) = 0;
    virtual void render(Text&) = 0;
    virtual void render(VertexArray&) = 0;
protected:
    Camera& m_camera;
};

#endif
