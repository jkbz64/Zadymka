#include <ECS/GameState.hpp>
#include <Graphics/Window.hpp>
#include <ECS.hpp>

std::unordered_map<std::string, sol::table> GameState::m_registeredSystems;

void GameState::registerSystem(const std::string& systemName, sol::table system)
{
    m_registeredSystems[systemName] = system;
}

GameState::GameState(sol::this_state L) :
    m_lua(L),
    m_camera(),
    m_eventManager(),
    m_entityManager(L, m_eventManager),
    m_nullSystem(L)
{
    m_table = m_lua.create_table();
    m_init = [](){};
    m_cleanup = [](){};
    m_update = [](double){};
    m_fixedUpdate = [](double){};
    m_draw = [](Window&, double){};
    m_table["systems"] = std::unordered_map<std::string, std::reference_wrapper<System>>();
}

GameState::GameState(sol::this_state L, sol::table state) :
    GameState(L)
{
    if(state["init"].valid())
        m_init = [state, this]() { state["init"].call(this); };
    if(state["cleanup"].valid())
        m_cleanup = [state, this]() { state["cleanup"].call(this); };
    if(state["update"].valid())
        m_update = [state, this](double dt) { state["update"].call(this, dt); };
    if(state["fixedUpdate"].valid())
        m_fixedUpdate = [state, this](double dt) { state["fixedUpdate"].call(this, dt); };
    if(state["draw"].valid())
        m_draw = [state, this](Window &window, double alpha) { state["draw"].call(this, window, alpha); };
    //Add systems if there were any specified
    sol::table systems = state["systems"];
    if(systems.valid())
    {
        std::unordered_map<std::string, std::reference_wrapper<System>> &addedSystems = m_table["systems"] = std::unordered_map<std::string, std::reference_wrapper<System>>();
        for(std::pair<sol::object, sol::object> system : systems)
            addedSystems.emplace(system.second.as<std::string>(), addSystem(system.second.as<std::string>()));
    }
    
    init();
}

GameState::~GameState()
{
    cleanup();
}

void GameState::init() const
{
    m_init();
}

void GameState::cleanup() const
{
    m_cleanup();
}

void GameState::update(double dt) const
{
    m_update(dt);
}

void GameState::fixedUpdate(double dt) const
{
    m_fixedUpdate(dt);
}

void GameState::draw(Window &window, double alpha) const
{
    m_draw(window, alpha);
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