#include <Physics/Body.hpp>
#include <Physics/World.hpp>
#include <Lua.hpp>
#include <Physics/Util.hpp>

void Body::registerClass()
{
    Lua::getState().new_usertype<Body>("Body",
                                       sol::constructors<Body(sol::table)>(),
                                       "getPosition", [](Body& body) { return std::make_tuple(body.getPosition().x, body.getPosition().y); },
                                       "getSize", [](Body& body) { return std::make_tuple(body.getSize().x, body.getSize().y); },
                                       "getVelocity", [](Body& body) { return std::make_tuple(body.getVelocity().x, body.getVelocity().y); },
                                       "setVelocity", [](Body& body, float x, float y) { body.setVelocity(glm::vec2(x, y)); }
    );
}

Body::Body() :
    m_world(nullptr),
    m_body(nullptr)
{

}

Body::Body(sol::table t) :
    m_world(nullptr),
    m_body(nullptr)
{
    if(t.valid())
    {
        m_type = static_cast<b2::BodyType>(t.get_or("bodyType", 0));
        m_position.x = t.get_or("x", 0.f);
        m_position.y = t.get_or("y", 0.f);
        m_size.x = t.get_or("width", 0.f);
        m_size.y = t.get_or("height", 0.f);
    }
}

Body::~Body()
{

}

const glm::vec2& Body::getPosition()
{
    return m_position;
}

const glm::vec2& Body::getSize()
{
    return m_size;
}

const glm::vec2& Body::getVelocity()
{
    return m_velocity;
}

void Body::setVelocity(const glm::vec2 &vel)
{
    if(m_body)
        m_body->SetLinearVelocity(vecToBoxVec(vel));
}
