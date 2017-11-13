#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <Window.hpp>
#include <Entity.hpp>

class EventManager;

class System
{
public:
    static void registerClass();
    System();
    System(sol::object);
    System(const System&) = delete;
    System(System&&) = delete;
    System& operator=(const System&) = delete;
    System& operator=(System&&) = delete;
    ~System() = default;
    void init(EventManager&, EntityManager&);
    void update(float);
    void fixedUpdate(float);
    void draw(Window&, float);
    void onCreatedEntity(sol::table);
protected:
    sol::object m_system;
    sol::function m_init;
    sol::function m_update;
    sol::function m_fixedUpdate;
    sol::function m_draw;
    std::vector<std::string> m_requiredComponents;
    std::vector<std::reference_wrapper<Entity>> m_entities;
};

inline void System::onCreatedEntity(sol::table table)
{
    Entity &entity = table.get<Entity>("entity");
    if(entity.hasComponents(m_requiredComponents) &&
       std::find_if(std::begin(m_entities),
                    std::end(m_entities),
                    [&entity](Entity& e){ return e.getID() == entity.getID(); }) == std::end(m_entities)
    )
        m_entities.emplace_back(entity);
}

#endif
