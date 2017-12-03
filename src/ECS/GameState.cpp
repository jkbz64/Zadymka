#include <include/ECS/GameState.hpp>
#include <Graphics/Window.hpp>
#include <include/ECS.hpp>
#include <Lua.hpp>

void GameState::registerClass(sol::table module)
{
    module.new_usertype<GameState>("GameState", sol::constructors<GameState(), GameState(sol::table)>(),
                                            "camera", &GameState::m_camera,
                                            "eventManager", &GameState::m_eventManager,
                                            "entityManager", &GameState::m_entityManager,
                                            "addSystem", &GameState::addSystem,
                                            "getSystem", &GameState::getSystem,
                                            "removeSystem", &GameState::removeSystem,
                                            sol::meta_function::index, [](GameState& state, const std::string& key)
                                            {
                                                return state.m_table[key];
                                            },
                                            sol::meta_function::new_index, [](GameState& state, const std::string& key, sol::object value)
                                            {
                                                state.m_table[key] =  value;
                                            },
                                            "update", &GameState::update,
                                            "fixedUpdate", &GameState::fixedUpdate,
                                            "draw", &GameState::draw
    );
}

GameState::GameState() :
    m_camera(),
    m_eventManager(),
    m_entityManager(m_eventManager)
{
    m_table = Lua::getState().create_table();
    m_cleanup = [](){};
    m_update = [](double){};
    m_fixedUpdate = [](double){};
    m_draw = [](Window&, double){};
    m_table["systems"] = std::unordered_map<std::string, std::reference_wrapper<System>>();
}

GameState::GameState(sol::table state) :
    GameState()
{
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
}

GameState::~GameState()
{
    cleanup();
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
    sol::table systemTable = ECS::getSystem(systemName);
    m_systems.emplace(systemName, systemTable);
    auto& system = m_systems[systemName];
    system.init.call(&system, m_eventManager, m_entityManager);
    std::unordered_map<std::string, std::reference_wrapper<System>>& addedSystems = m_table["systems"];
    addedSystems.emplace(systemName, system);
    return system;
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
}
