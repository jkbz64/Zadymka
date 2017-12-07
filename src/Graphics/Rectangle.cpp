#include <Graphics/Rectangle.hpp>
#include <Graphics/Renderer.hpp>

void Rectangle::registerClass(sol::table module)
{
    module.new_usertype<Rectangle>("Rectangle",
                                            sol::constructors<Rectangle(unsigned int, unsigned int)>(),
                                            "getPosition", &Rectangle::getPosition,
                                            "setPosition", &Rectangle::setPosition,
                                            "getSize", &Rectangle::getSize,
                                            "setSize", &Rectangle::setSize,
                                            "getColor", &Rectangle::getColor,
                                            "setColor", &Rectangle::setColor,
                                            sol::base_classes, sol::bases<Drawable>()
    );
}

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

void Rectangle::setPosition(const glm::vec2 &position)
{
    translate(glm::vec2(position.x, position.y));
}

const glm::vec2& Rectangle::getPosition()
{
    return m_translation;
}

void Rectangle::setSize(const glm::vec2 &size)
{
    scale(size.x, size.y);
}

const glm::vec2& Rectangle::getSize()
{
    return m_scale;
}

const Color& Rectangle::getColor() const
{
    return m_color;
}

void Rectangle::setColor(const Color& color)
{
    m_color = color;
}

void Rectangle::draw(Renderer *renderer)
{
    renderer->render(*this);
}
