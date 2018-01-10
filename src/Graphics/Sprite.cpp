#include <Graphics/Sprite.hpp>
#include <Graphics/Renderer.hpp>

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

const Texture& Sprite::texture() const
{
    return m_texture;
}

void Sprite::setTexture(const Texture &texture)
{
    m_texture = texture;
    if(size().x == 0 && size().y == 0)
        setSize(m_texture.size());
}

const glm::vec2& Sprite::position() const
{
    return m_translation;
}

const glm::vec2& Sprite::size() const
{
    return m_scale;
}

void Sprite::setPosition(const glm::vec2& position)
{
    translate(position);
}

void Sprite::setSize(const glm::vec2& size)
{
    scale(size.x, size.y);
}

void Sprite::draw(Renderer* renderer)
{
    renderer->render(*this);
}