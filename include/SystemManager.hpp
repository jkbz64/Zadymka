#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP
#include <unordered_map>
#include <Lua.hpp>
#include <System.hpp>

class EventManager;

class SystemManager
{
public:
    static void registerClass();
    SystemManager(EventManager&, EntityManager&);
    std::shared_ptr<System> addSystem(const std::string&);
    std::shared_ptr<System> getSystem(const std::string&);
    template<class T>
    static void registerSystem(const std::string&);
private:
    EventManager& m_eventManager;
    EntityManager& m_entityManager;
    std::unordered_map<std::string, std::shared_ptr<System>> m_systems;
    static std::unordered_map<std::string, std::function<std::shared_ptr<System>()>> m_registeredSystems;
};

template<class T>
inline void SystemManager::registerSystem(const std::string& systemName)
{
    static_assert(std::is_base_of<System, T>::value, " must derive from System");
    m_registeredSystems[systemName] = []() -> std::shared_ptr<T>
    {
        return std::make_shared<T>();
    };
}

#endif
