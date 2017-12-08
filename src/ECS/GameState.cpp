#include <ECS/GameState.hpp>
#include <Graphics/Window.hpp>
#include <ECS.hpp>

std::unordered_map<std::string, sol::table> GameState::m_registeredSystems;

void GameState::registerSystem(const std::string& systemName, sol::table system)
{
    m_registeredSystems[systemName] = system;
}

GameState::GameState(sol::this_state L) :
    Scriptable<GameState>(),
    m_camera(),
    m_eventManager(),
    m_entityManager(L, m_eventManager),
    m_nullSystem(L)
{

}

GameState::GameState(sol::this_state L, sol::table state) :
        Scriptable<GameState>(L, state),
        m_camera(),
        m_eventManager(),
        m_entityManager(L, m_eventManager),
        m_nullSystem(L)
{
    m_table["systems"] = std::unordered_map<std::string, std::reference_wrapper<System>>();
    //Add systems if there were any specified
    sol::table systems = state["systems"];
    if(systems.valid())
    {
        std::unordered_map<std::string, std::reference_wrapper<System>> &addedSystems = m_table["systems"] = std::unordered_map<std::string, std::reference_wrapper<System>>();
        for(std::pair<sol::object, sol::object> system : systems)
            addedSystems.emplace(system.second.as<std::string>(), addSystem(system.second.as<std::string>()));
    }
    
    sol::function init = m_table["init"];
    init.call(*this);
}

GameState::~GameState()
{

}

System& GameState::addSystem(const std::string& systemName)
{
    sol::table systemTable = m_registeredSystems[systemName];
    if(systemTable.valid())
    {
        m_systems.emplace(std::piecewise_construct,
                          std::forward_as_tuple(systemName),
                          std::forward_as_tuple(m_lua.lua_state(), systemTable));
        System &system = m_systems[systemName];
        system.init.call(&system, m_eventManager, m_entityManager);
        std::unordered_map<std::string, std::reference_wrapper<System>> &addedSystems = m_table["systems"];
        addedSystems.emplace(systemName, system);
        return system;
    }
    return m_nullSystem;
}

void GameState::removeSystem(const std::string& systemName)
{
    if(m_systems.find(systemName) != std::end(m_systems))
    {
        std::unordered_map<std::string, std::reference_wrapper<System>>& addedSystems = m_table["systems"];
        addedSystems.erase(addedSystems.find(systemName));
        m_systems.erase(m_systems.find(systemName));
    }
}

System& GameState::getSystem(const std::string& systemName)
{
    if(m_systems.find(systemName) != std::end(m_systems))
        return m_systems[systemName];
    return m_nullSystem;
}

const Camera& GameState::getCamera() const
{
    return m_camera;
}