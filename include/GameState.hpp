#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <Lua.hpp>
#include <Camera.hpp>
#include <EventManager.hpp>
#include <SystemManager.hpp>
#include <EntityManager.hpp>
#include <Window.hpp>

class GameState
{
public:
    GameState();
    GameState(sol::object);
    GameState(const GameState&) = delete;
    GameState& operator=(const GameState&) = delete;
    GameState(GameState&&) = delete;
    GameState& operator=(GameState&&) = delete;
    ~GameState();

    void cleanup();
    void update(float dt) const;
    void fixedUpdate(float dt) const;
    void draw(Window& window, float alpha) const;

    const Camera& getCamera() const;
    const EntityManager& getEntityManager() const;
    sol::object getState() const;
protected:
    sol::object m_state;
    Camera m_camera;
    EventManager m_eventManager;
    EntityManager m_entityManager;
    SystemManager m_systemManager;
    sol::function m_cleanup;
    sol::function m_update;
    sol::function m_fixedUpdate;
    sol::function m_draw;
};

inline const Camera& GameState::getCamera() const
{
    return m_camera;
}

inline const EntityManager& GameState::getEntityManager() const
{
    return m_entityManager;
}

inline sol::object GameState::getState() const
{
    return m_state;
}

#endif
