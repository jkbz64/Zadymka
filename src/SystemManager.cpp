#include <SystemManager.hpp>
#include <LuaSystem.hpp>
#include <EventManager.hpp>

std::unordered_map<std::string, std::function<std::shared_ptr<System>()>> SystemManager::m_registeredSystems;

void SystemManager::registerClass()
{
    Lua::getState().new_usertype<SystemManager>("SystemManager",
                                                sol::constructors<SystemManager(EventManager&)>(),
                                                "addSystem", [](SystemManager& mgr, const std::string& systemName) -> sol::object
                                                {
                                                    return mgr.addSystem(systemName)->getLuaRef();
                                                }
                                                );
}

SystemManager::SystemManager(EventManager& mgr) : m_eventManager(mgr)
{

}

std::shared_ptr<System> SystemManager::addSystem(const std::string& systemName)
{
    if(m_registeredSystems.find(systemName) != std::end(m_registeredSystems))
        m_systems[systemName] = m_registeredSystems[systemName]();
    else
    {
        sol::object system = Lua::getState().safe_script("return dofile('systems/" + systemName + ".lua')()");
        m_systems[systemName] = std::make_shared<LuaSystem>(systemName, system);
    }
    m_eventManager.subscribe("EntityCreated", *m_systems[systemName].get(), &System::onCreatedEntity);
    m_systems[systemName]->initialize(m_eventManager);
    return m_systems[systemName];
}

std::shared_ptr<System> SystemManager::getSystem(const std::string& systemName)
{
    if(m_systems.find(systemName) != std::end(m_systems))
        return m_systems[systemName];
    else
        return std::shared_ptr<System>();
}
