#include <Graphics/Rectangle.hpp>
#include <Graphics/Renderer.hpp>
#include <utility>

Rectangle::Rectangle()
{

}

Rectangle::Rectangle(unsigned int width, unsigned int height) :
    Rectangle()
{
    setSize(glm::vec2(width, height));
}

Rectangle::Rectangle(const Rectangle &other) :
    Transformable(other)
{

}

Rectangle::Rectangle(Rectangle&& other) :
    Transformable(std::move(other))
{

}

Rectangle& Rectangle::operator =(const Rectangle& other)
{
    if(this != &other)
        static_cast<Transformable>(*this) = static_cast<Transformable>(other);
    return *this;
}

Rectangle& Rectangle::operator =(Rectangle&& other)
{
    if(this != &other)
        static_cast<Transformable>(*this) = std::move(static_cast<Transformable>(other));
    return *this;
}

const glm::vec2& Rectangle::position()
{
    return m_translation;
}

const glm::vec2& Rectangle::size()
{
    return m_scale;
}

const Color& Rectangle::color() const
{
    return m_color;
}

void Rectangle::setPosition(const glm::vec2 &position)
{
    translate(glm::vec2(position.x, position.y));
}

void Rectangle::setSize(const glm::vec2 &size)
{
    scale(size.x, size.y);
}

void Rectangle::setColor(const Color& color)
{
    m_color = color;
}

void Rectangle::draw(Renderer *renderer)
{
    renderer->render(*this);
}
