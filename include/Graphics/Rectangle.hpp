#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <Graphics/Drawable.hpp>
#include <Graphics/Transformable.hpp>

class Rectangle : public Drawable<Rectangle>, public Transformable
{
public:
    static void registerClass();
    Rectangle(unsigned int, unsigned int);
    virtual ~Rectangle() = default;
protected:
    virtual void draw(Window&);
};

#endif
