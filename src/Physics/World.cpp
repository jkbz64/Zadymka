#include <Physics/World.hpp>
#include <Lua.hpp>
#include <Physics/Util.hpp>

void World::registerClass()
{
    Lua::getState().new_usertype<World>("World",
                                        sol::constructors<World(), World(float, float)>(),
                                        "addBody", &World::addBody,
                                        "removeBody", &World::removeBody,
                                        "step", &World::step
                                        );
}

World::World() :
    b2::World(b2::Vec2(0.f, 0.f))
{

}

World::World(float x, float y) :
    b2::World(b2::Vec2(floatToBoxFloat(x), floatToBoxFloat(y)))
{

}

void World::addBody(Body& body)
{
    if(body.m_body == nullptr && body.m_world == nullptr)
    {
        auto& def = body.m_bodyDef;
        def.type = b2::BodyType::dynamicBody;
        const auto center = vecToBoxVec(glm::vec2(body.getPosition().x + body.getSize().x / 2.f, body.getPosition().y + body.getSize().y / 2.f));
        def.position.Set(center.x, center.y);
        body.m_body = CreateBody(&def);
        auto& shape = body.m_shape;
        const auto size = vecToBoxVec(body.getSize());
        shape.SetAsBox(size.x / 2.f, size.y / 2.f);
        auto& fixture = body.m_fixture;
        fixture.shape = &shape;
        fixture.density = 1;
        body.m_body->CreateFixture(&fixture);
        m_bodies.emplace_back(body);
    }
}

void World::removeBody(Body &body)
{
    if(body.m_world == this && body.m_body != nullptr)
    {
        DestroyBody(body.m_body);
        m_bodies.erase(std::remove_if(std::begin(m_bodies), std::end(m_bodies), [&body](std::reference_wrapper<Body>& b)
        {
            return &b.get() == &body;
        }));

        body.m_world = nullptr;
        body.m_body = nullptr;
    }
}

void World::step(double dt)
{
    Step(dt, 6, 3);
    for(auto& b : m_bodies)
    {
        Body& body = b.get();
        b2::Body& b2body = *body.m_body;
        glm::vec2 newPos = boxToVec(b2body.GetPosition());
        body.m_velocity = boxToVec(b2body.GetLinearVelocity());
        newPos -= body.getSize() / 2.f;
        body.m_position = newPos;
    }
}

std::vector<std::reference_wrapper<Body>>& World::getBodies()
{
    return m_bodies;
}
