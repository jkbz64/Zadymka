#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

class Renderer;

class Drawable
{
public:
    Drawable() = default;
    virtual ~Drawable() = default;
protected:
    friend class RenderTarget;
    virtual void draw(Renderer* renderer) = 0;
};

#endif
