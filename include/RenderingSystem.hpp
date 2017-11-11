#ifndef RENDERINGSYSTEM_HPP
#define RENDERINGSYSTEM_HPP

#include <System.hpp>
#include <EventManager.hpp>
#include <Entity.hpp>
#include <iostream>

template<typename T>
inline T lerp(T v0, T v1, float t)
{
    return (1.f - t) * v0 + t * v1;
}

class RenderingSystem : public System
{
public:
    static void registerClass()
    {
        Lua::getState().new_usertype<RenderingSystem>("RenderingSystem",
                                                      "new", sol::no_constructor,
                                                      "saveCurrentState", &RenderingSystem::saveCurrentState,
                                                      sol::base_classes, sol::bases<System>());
        SystemManager::registerSystem<RenderingSystem>("RenderingSystem");
    }

    RenderingSystem() :
        System("RenderingSystem")
    {
        m_luaRef = sol::make_object(Lua::getState(), this);
    }

    virtual void initialize(EventManager &mgr, EntityManager& e_mgr) override
    {
        mgr.subscribe("EntityCreated", *this, &RenderingSystem::onEntityCreated);
    }

    virtual void fixedUpdate(float dt) override
    {
        saveCurrentState();
    }

    virtual void draw(Window& window, float alpha) override
    {
        for(auto& entityRef : m_entities)
        {
            auto& entity = entityRef.get();
            sf::Vector2f lerped = lerp(entity.getPreviousPosition(), entity.getPosition(), alpha);
            sf::RectangleShape shape(sf::Vector2f(100, 100));
            shape.setPosition(lerped);
            window.draw(shape);
        }
    }

    void onEntityCreated(sol::table eventTable)
    {
        m_entities.emplace_back(eventTable.get<Entity>("entity"));
    }

    void saveCurrentState()
    {
        for(auto& entityRef : m_entities)
        {
            auto& entity = entityRef.get();
            entity.m_previousPosition = entity.m_position;
        }
    }
protected:
    std::vector<std::reference_wrapper<Entity>> m_entities;
};

#endif
