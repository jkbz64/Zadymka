#ifndef RENDERER_HPP
#define RENDERER_HPP

class Drawable;
class Rectangle;
class Sprite;
class Text;
class VertexArray;
class Tilemap;

class Renderer
{
public:
    Renderer() { };
    virtual ~Renderer() { };
    virtual void render(Rectangle&) = 0;
    virtual void render(Sprite&) = 0;
    virtual void render(Text&) = 0;
    virtual void render(Tilemap&) = 0;
};

#endif
