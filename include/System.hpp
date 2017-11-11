#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <Window.hpp>
#include <Entity.hpp>

class EventManager;

class System
{
public:
    static void registerClass()
    {
        Lua::getState().new_usertype<System>("System",
                                             "new", sol::no_constructor,
                                             "update", &System::update,
                                             "fixedUpdate", &System::fixedUpdate,
                                             "draw", &System::draw,
                                             "entities", &System::m_entities);
    }

    System(const std::string& systemName, std::vector<std::string> requiredComponents = std::vector<std::string>()) :
        m_name(systemName),
        m_requiredComponents(std::move(requiredComponents))
    { }
    virtual ~System() = default;
    virtual void initialize(EventManager&, EntityManager&) = 0;
    virtual void update(float) {}
    virtual void fixedUpdate(float) {}
    virtual void draw(Window&, float) {}
    const std::string& getName() const;
    sol::object getLuaRef() const;
    void onCreatedEntity(sol::table);
    void onComponentAdded(sol::table);
protected:
    std::string m_name;
    sol::object m_luaRef;
    std::vector<std::string> m_requiredComponents;
    std::vector<std::reference_wrapper<Entity>> m_entities;
};

inline const std::string& System::getName() const
{
    return m_name;
}

inline sol::object System::getLuaRef() const
{
    return m_luaRef;
}

inline void System::onCreatedEntity(sol::table table)
{
    Entity &entity = table.get<Entity>("entity");
    if(entity.hasComponents(m_requiredComponents) &&
       std::find_if(std::begin(m_entities),
                    std::end(m_entities),
                    [&entity](Entity& e){ return e.getID() == entity.getID(); }) == std::end(m_entities))
        m_entities.emplace_back(entity);
}

inline void System::onComponentAdded(sol::table table)
{
    Lua::scriptArgs(
    R"(
    local entity = arg[1].component.entity
    local found = false
    for k, v in pairs(arg[2]) do
        if v:get():getID() == entity:getID() then found = true end
    end
    print('lul')
    if found == false then arg[2]:add(entity) end
    )", table, &m_entities);
}

#endif
