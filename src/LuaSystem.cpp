#include <LuaSystem.hpp>
#include <SystemManager.hpp>
#include <EventManager.hpp>
#include <EntityManager.hpp>

void LuaSystem::registerClass()
{
    Lua::getState().new_usertype<LuaSystem>("LuaSystem",
                                            "new", sol::no_constructor,
                                            sol::meta_function::index, [](const std::string& name)
                                            {
                                                return [name](LuaSystem& system, sol::variadic_args args)
                                                {
                                                    return Lua::getState()[system.getName()][name].call(system.getLuaRef(), args);
                                                };
                                            }
                                            );
}

LuaSystem::LuaSystem(const std::string& systemName, sol::object system) :
    System(systemName)
{
    m_luaRef = system;
    m_systemTable = m_luaRef;
    Lua::scriptArgs("arg[1].entities = arg[2]", system, m_entities);

    m_initialize = [this](EventManager& mgr, EntityManager& e_mgr)
    {
        m_systemTable["init"].call(m_luaRef, mgr, e_mgr);
    };

    m_update = [this](float dt)
    {
        m_systemTable["update"].call(m_luaRef, dt);
    };

    m_fixedUpdate = [this](float dt)
    {
        m_systemTable["fixedUpdate"].call(m_luaRef, dt);
    };

    m_draw = [this](Window& window, float alpha)
    {
        m_systemTable["draw"].call(m_luaRef, window, alpha);
    };

    sol::table requiredComponents = m_systemTable.get_or("requiredComponents", sol::table{});
    for(const auto& componentPair : requiredComponents)
        m_requiredComponents.emplace_back(componentPair.second.as<std::string>());
}

void LuaSystem::initialize(EventManager& mgr, EntityManager& e_mgr)
{
    m_initialize(mgr, e_mgr);
}

void LuaSystem::update(float dt)
{
    m_update(dt);
}

void LuaSystem::fixedUpdate(float dt)
{
    m_fixedUpdate(dt);
}

void LuaSystem::draw(Window& window, float alpha)
{
    m_draw(window, alpha);
}
