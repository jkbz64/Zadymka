#include <SystemManager.hpp>
#include <LuaSystem.hpp>

std::unordered_map<std::string, std::function<std::shared_ptr<System>()>> SystemManager::m_registeredSystems;

void SystemManager::registerClass()
{
    Lua::getState().new_usertype<SystemManager>("SystemManager",
                                                sol::constructors<SystemManager()>(),
                                                "addSystem", [](SystemManager& mgr, const std::string& systemName) -> sol::object
                                                {
                                                    return mgr.addSystem(systemName)->getLuaRef();
                                                }
                                                );
}

SystemManager::SystemManager()
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
    subscribe("EntityCreated", *m_systems[systemName].get(), &System::onCreatedEntity);
    m_systems[systemName]->initialize(*this);    
    return m_systems[systemName];
}

std::shared_ptr<System> SystemManager::getSystem(const std::string& systemName)
{
    if(m_systems.find(systemName) != std::end(m_systems))
        return m_systems[systemName];
    else
        return std::shared_ptr<System>();
}

void SystemManager::subscribe(const std::string& eventName, sol::object obj, sol::function f)
{
    if(m_eventCallbacks.find(eventName) == std::end(m_eventCallbacks))
        m_eventCallbacks[eventName] = std::vector<std::function<void(sol::table)>>();
    std::vector<std::function<void(sol::table)>>& callbacks = m_eventCallbacks[eventName];
    callbacks.emplace_back([obj, f](sol::table table)
    {
        f.call(obj, table);
    });
}

void SystemManager::emit(const std::string& eventName, sol::table table)
{
    if(m_eventCallbacks.find(eventName) != std::end(m_eventCallbacks))
    {
        const auto& callbacks = m_eventCallbacks[eventName];
        std::for_each(std::begin(callbacks), std::end(callbacks), [&table](std::function<void(sol::table)> f)
        {
            f(table);
        });
    }
}
