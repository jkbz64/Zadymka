#ifndef WORLD_HPP
#define WORLD_HPP
#include <forward_list>
#include <vector>
#include <Physics/Body.hpp>
#include <Lua.hpp>
#include <Box2D/Box2D.hpp>
#include <functional>

class World : protected b2::World
{
public:
    static void registerClass();
    World();
    World(float, float);
    World(const World&) = delete;
    World(World&&) = delete;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = delete;
    virtual ~World() = default;
    void step(double);
    void addBody(Body&);
    void removeBody(Body&);
    std::vector<std::reference_wrapper<Body>>& getBodies();
private:
    std::vector<std::reference_wrapper<Body>> m_bodies;
};

#endif
