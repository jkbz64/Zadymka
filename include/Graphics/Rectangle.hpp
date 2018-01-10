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
    
    const glm::vec2& position();
    const glm::vec2& size();
    const Color& color() const;
    
    void setPosition(const glm::vec2&);
    void setSize(const glm::vec2&);
    void setColor(const Color&);
protected:
    friend class Graphics;
    void draw(Renderer*) override;
    Color m_color;
};

#endif
