#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <Graphics/Drawable.hpp>
#include <Graphics/Color.hpp>

class Rectangle : public Drawable<Rectangle>
{
public:
    static void registerClass();
    Rectangle();
    Rectangle(unsigned, unsigned);
    Rectangle(const Rectangle&);
    Rectangle& operator=(const Rectangle&);
    Rectangle(Rectangle&&);
    Rectangle& operator=(Rectangle&&);
    virtual ~Rectangle() = default;
    void setPosition(const glm::vec2&);
    const glm::vec2& getPosition();
    void setSize(const glm::vec2&);
    const glm::vec2& getSize();
protected:
    virtual void draw(Window&);
};

#endif
