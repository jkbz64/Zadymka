#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <Lua.hpp>
#include <Camera.hpp>
#include <EntityManager.hpp>
#include <Window.hpp>

//More like proxy, not even real game state
class GameState
{
public:
    GameState()
    {
        m_cleanup = [](){};
        m_update = [](float){};
        m_fixedUpdate = [](float){};
        m_draw = [](Window&, float){};
    }

    ~GameState()
    {
        cleanup();
    }

    GameState(sol::object gameState)
    {
        m_state = gameState;
        sol::table table = m_state;
        m_cleanup = [this, table]()
        {
            table["cleanup"].call(m_state);
        };

        m_update = [this, table](float dt)
        {
            table["update"].call(m_state, dt);
        };

        m_fixedUpdate = [this, table](float dt)
        {
            table["fixedUpdate"].call(m_state, dt);
        };

        m_draw = [this, table](Window& window, float alpha)
        {
            table["draw"].call(m_state, window, alpha);
        };
        m_view = table["camera"];
        m_entityManager = table["entityManager"];
    }

    void cleanup()
    {
        m_cleanup();
    }

    void update(float dt) const
    {
        m_update(dt);
    }

    void fixedUpdate(float dt) const
    {
        m_fixedUpdate(dt);
    }

    void draw(Window& window, float alpha) const
    {
        m_draw(window, alpha);
    }

    sf::View getView() const
    {
        return m_view.as<Camera>();
    }

    EntityManager& getEntityManager() const
    {
        return m_entityManager.as<EntityManager>();
    }

    sol::object getState()
    {
        return m_state;
    }
protected:
    sol::object m_state;
    std::function<void()> m_cleanup;
    std::function<void(float)> m_update;
    std::function<void(float)> m_fixedUpdate;
    std::function<void(Window&, float)> m_draw;
    sol::object m_view;
    sol::object m_entityManager;
};

#endif
