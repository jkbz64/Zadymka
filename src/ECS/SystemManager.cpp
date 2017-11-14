#include <ECS/SystemManager.hpp>
#include <ECS/EventManager.hpp>
#include <ECS/EntityManager.hpp>
#include <iostream>

void SystemManager::registerClass()
{
    Lua::getState().new_usertype<SystemManager>("SystemManager",
                                                sol::constructors<SystemManager(EventManager&, EntityManager&)>(),
                                                "addSystem", &SystemManager::addSystem,
                                                "getSystem", &SystemManager::getSystem
                                                );
}

SystemManager::SystemManager(EventManager& mgr, EntityManager& e_mgr) :
    m_eventManager(mgr),
    m_entityManager(e_mgr)
{

}

System& SystemManager::addSystem(const std::string& systemName)
{
    sol::object system;
    try
    {
        system = Lua::getState().safe_script("return dofile('systems/' .. '" + systemName + "' .. '.lua')()");
    }
    catch(sol::error& e)
    {
        std::cerr << "Couldn't find " + systemName + " in systems directory\n";
        return m_nullSystem;
    }
    m_systems.emplace(systemName, system);
    m_eventManager.subscribe("EntityCreated", m_systems[systemName], &System::onCreatedEntity);
    m_eventManager.subscribe("EntityDestroyed", m_systems[systemName], &System::onDestroyedEntity);
    m_systems[systemName].init(m_eventManager, m_entityManager);
    return m_systems[systemName];
}

System& SystemManager::getSystem(const std::string& systemName)
{
    if(m_systems.find(systemName) != std::end(m_systems))
        return m_systems[systemName];
    else
        return m_nullSystem;
}
