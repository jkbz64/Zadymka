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
    System& addSystem(const std::string&);
    System& getSystem(const std::string&);
private:
    EventManager& m_eventManager;
    EntityManager& m_entityManager;
    std::unordered_map<std::string, System> m_systems;
    System m_nullSystem;
};

#endif
