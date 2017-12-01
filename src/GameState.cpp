#include <GameState.hpp>
#include <Graphics/Window.hpp>

GameState::GameState() :
    m_camera(),
    m_eventManager(),
    m_entityManager(m_eventManager),
    m_systemManager(m_eventManager, m_entityManager)
{
    m_state = Lua::getState().script("return nil");
    sol::tie(m_cleanup, m_update, m_fixedUpdate, m_draw) = Lua::getState().script(
    R"(
    local nilf = function() end
    return nilf, nilf, nilf, nilf
    )");
}

GameState::GameState(sol::object state) :
    m_camera(),
    m_eventManager(),
    m_entityManager(m_eventManager),
    m_systemManager(m_eventManager, m_entityManager)
{
    sol::tie(m_cleanup, m_update, m_fixedUpdate, m_draw) = Lua::scriptArgs(
    R"(
    local state = arg[1]
    local returnWrappedFunction = function(f)
        if f ~= nil then
            return function(...) return f(state, ...) end
        else
            return nil
        end
    end
    local nilf = function(...) end
    state.camera = arg[2]
    state.eventManager = arg[3]
    state.entityManager = arg[4]
    state.systemManager = arg[5]
    state:init()
    return returnWrappedFunction(state.cleanup) or nilf,
           returnWrappedFunction(state.update) or nilf,
           returnWrappedFunction(state.fixedUpdate) or nilf,
           returnWrappedFunction(state.draw) or nilf
    )", state, &m_camera, &m_eventManager, &m_entityManager, &m_systemManager);
}

GameState::~GameState()
{
    cleanup();
}

void GameState::cleanup()
{
    m_cleanup.call();
}

void GameState::update(double dt) const
{
    m_update.call(dt);
}

void GameState::fixedUpdate(double dt) const
{
    m_fixedUpdate.call(dt);
}

void GameState::draw(Window &window, double alpha) const
{
    m_draw.call(window, alpha);
}
