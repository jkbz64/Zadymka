#include <Graphics/Transformable.hpp>
#include <Lua.hpp>
#include <glm/gtc/matrix_transform.hpp>

Transformable::Transformable() :
    m_modified(true),
    m_translation(0.f, 0.f),
    m_rotation(0.f),
    m_model(1.f)
{

}

Transformable::Transformable(const Transformable &other)
{
    m_modified = true;
    m_model = glm::mat4(1.f);
    m_translation = other.m_translation;
    m_rotation = other.m_rotation;
}

Transformable::Transformable(Transformable &&other)
{
    m_modified = true;
    m_model = glm::mat4(1.f);
    m_translation = std::move(other.m_translation);
    m_rotation = std::move(other.m_rotation);
}

Transformable& Transformable::operator =(const Transformable& other)
{
    if(this != &other)
    {
        m_modified = true;
        m_model = glm::mat4(1.f);
        m_translation = other.m_translation;
        m_rotation = other.m_rotation;
    }
    return *this;
}

Transformable& Transformable::operator =(Transformable&& other)
{
    if(this != &other)
    {
        m_modified = true;
        m_model = glm::mat4(1.f);
        m_translation = std::move(other.m_translation);
        m_rotation = std::move(other.m_rotation);
    }
    return *this;
}

void Transformable::translateBy(float dx, float dy)
{
    if(dx == 0.f || dx == 0.f)
       return;
    m_modified = true;
    m_translation.x += dx;
    m_translation.y += dy;
}

void Transformable::translate(const glm::vec2& translation)
{
    if(translation != m_translation)
        m_modified = true;
    m_translation = translation;
}

void Transformable::scale(float fx, float fy)
{
    if(fx != m_scale.x || fy != m_scale.y)
        m_modified = true;
    m_scale = glm::vec2(fx, fy);
}

void Transformable::rotate(float deg)
{
    if(deg != m_rotation)
        m_modified = true;
    m_rotation = deg;
}

const glm::mat4& Transformable::getModel()
{
    if(m_modified)
    {
        m_model = glm::mat4(1.f);
        m_model = glm::translate(m_model, glm::vec3(m_translation, 0.f));
        m_model = glm::scale(m_model, glm::vec3(m_scale, 1.f));
        if(m_rotation != 0)
            m_model = glm::rotate(m_model, glm::degrees(m_rotation), glm::vec3(1.0f, 0.0f, 0.0f));
        m_modified = false;
    }
    return m_model;
}

