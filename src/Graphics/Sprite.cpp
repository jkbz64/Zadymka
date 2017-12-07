#include <Graphics/Sprite.hpp>

void Sprite::registerClass(sol::table module)
{
    module.new_usertype<Sprite>("Sprite",
                                         sol::constructors<Sprite()>(),
                                         "getPosition", &Sprite::getPosition,
                                         "setPosition", &Sprite::setPosition,
                                         "getSize", &Sprite::getSize,
                                         "setSize", &Sprite::setSize,
                                         "getTexture", &Sprite::getTexture,
                                         "setTexture", &Sprite::setTexture,
                                         sol::base_classes, sol::bases<Drawable>()
    );
}

Sprite::Sprite()
{
    m_color = Color(255, 255, 255, 255);
}

Sprite::Sprite(const Sprite& other) :
    Rectangle(other)
{
    m_texture = other.m_texture;
}

Sprite::Sprite(Sprite&& other) :
    Rectangle(other)
{
    m_texture = other.m_texture;
}

Sprite& Sprite::operator =(const Sprite& other)
{
    if(this != &other)
    {
        static_cast<Transformable>(*this) = static_cast<Transformable>(other);
        m_texture = other.m_texture;
    }
    return *this;
}

Sprite& Sprite::operator =(Sprite&& other)
{
    if(this != &other)
    {
        static_cast<Transformable>(*this) = std::move(static_cast<Transformable>(other));
        m_texture = other.m_texture;
    }
    return *this;
}

void Sprite::setTexture(const Texture &texture)
{
    m_texture = texture;
    if(getSize() == glm::vec2(0, 0))
        setSize(m_texture.getSize());
}

const Texture& Sprite::getTexture() const
{
    return m_texture;
}

void Sprite::setPosition(const glm::vec2& position)
{
    translate(position);
}

const glm::vec2& Sprite::getPosition() const
{
    return m_translation;
}

void Sprite::setSize(const glm::vec2& size)
{
    scale(size.x, size.y);
}

const glm::vec2& Sprite::getSize() const
{
    return m_scale;
}