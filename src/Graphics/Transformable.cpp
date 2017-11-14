#include <Graphics/Transformable.hpp>
#include <Lua.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Transformable::registerClass()
{
    Lua::getState().new_usertype<Transformable>("Transformable",
                                                sol::constructors<Transformable()>(),
                                                "setPosition", &Transformable::setPosition,
                                                "getPosition", &Transformable::getPosition,
                                                "setRotation", &Transformable::setRotation,
                                                "getRotation", &Transformable::getRotation
    );
}

Transformable::Transformable() :
    m_modified(true),
    m_position(0.f, 0.f),
    m_rotation(0.f),
    m_model(1.f)
{

}

void Transformable::setPosition(float x, float y)
{
    if(x != m_position.x || y != m_position.y)
        m_modified = true;
    m_position = glm::vec2(x, y);
}

const glm::vec2& Transformable::getPosition()
{
    return m_position;
}

void Transformable::setSize(unsigned int w, unsigned int h)
{
    if(w != m_size.x || h != m_size.y)
        m_modified = true;
    m_size = glm::vec2(w, h);
}

const glm::vec2& Transformable::getSize()
{
    return m_size;
}

void Transformable::setRotation(float r)
{
    if(r != m_rotation)
        m_modified = true;
    m_rotation = r;
}

float Transformable::getRotation()
{
    return m_rotation;
}

const glm::mat4& Transformable::getModel()
{
    if(m_modified)
    {
        m_model = glm::mat4(1.f);
        m_model = glm::translate(m_model, glm::vec3(m_position, 0.f));
        if(m_rotation != 0)
            m_model = glm::rotate(m_model, glm::degrees(m_rotation), glm::vec3(1.0f, 0.0f, 0.0f));
        m_model = glm::scale(m_model, glm::vec3(m_size.x, m_size.y, 0.f));
        m_modified = false;
    }
    return m_model;
}

