#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <Graphics/Drawable.hpp>
#include <Graphics/Color.hpp>
#include <Graphics/Transformable.hpp>

class Rectangle : public Drawable, public Transformable
{
public:
    Rectangle();
    Rectangle(unsigned, unsigned);
    Rectangle(const Rectangle&);
    Rectangle& operator=(const Rectangle&);
    Rectangle(Rectangle&&);
    Rectangle& operator=(Rectangle&&);
    ~Rectangle() = default;
    void setPosition(const glm::vec2&);
    const glm::vec2& getPosition();
    void setSize(const glm::vec2&);
    const glm::vec2& getSize();
    const Color& getColor() const;
    void setColor(const Color&);
protected:
    void draw(Renderer*) override;
    Color m_color;
};

#endif
