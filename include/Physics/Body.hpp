#ifndef BODY_HPP
#define BODY_HPP
#include <glm/vec2.hpp>
#include <Box2D/Box2D.hpp>
#include <Lua.hpp>

class World;

class Body
{
public:
    static void registerClass();
    Body();
    Body(sol::table);
    Body(const Body&) = delete;
    Body(Body&&) = delete;
    Body& operator=(const Body&) = delete;
    Body& operator=(Body&&) = delete;
    ~Body();
    const b2::BodyType& getType();
    const glm::vec2& getPosition();
    const glm::vec2& getSize();
    const glm::vec2& getVelocity();
    void setVelocity(const glm::vec2&);
private:
    friend class World;
    World *m_world;
    b2::Body* m_body;
    b2::BodyType m_type;
    glm::vec2 m_position;
    glm::vec2 m_size;
    glm::vec2 m_velocity;

    //World's stuff
    b2::BodyDef m_bodyDef;
    b2::FixtureDef m_fixture;
    b2::PolygonShape m_shape;
};

#endif
