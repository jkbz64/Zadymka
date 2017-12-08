#ifndef RENDERER_HPP
#define RENDERER_HPP

class Drawable;
class Rectangle;
class Sprite;
class Text;
class VertexArray;

class Renderer
{
public:
    Renderer() = default;
    virtual ~Renderer() = default;
    virtual void render(Rectangle&) = 0;
    virtual void render(Sprite&) = 0;
    virtual void render(Text&) = 0;
};

#endif
