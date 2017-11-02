#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <sol/function.hpp>
#include <sol/object.hpp>

//More like proxy, not even real game state
class GameState
{
public:
    GameState()
    {
        m_cleanup = [](){};
        m_update = [](float){};
        m_fixedUpdate = [](float){};
        m_draw = [](){};
    }

    ~GameState()
    {
        cleanup();
    }

    GameState(sol::object gameState)
    {
        m_state = gameState;
        sol::userdata ud = gameState;
        sol::table metatable = ud[sol::metatable_key];
        m_cleanup = [metatable, gameState]()
        {
            metatable["cleanup"].call(gameState);
        };

        m_update = [metatable, gameState](float dt)
        {
            metatable["update"].call(gameState, dt);
        };

        m_fixedUpdate = [metatable, gameState](float dt)
        {
            metatable["fixedUpdate"].call(gameState, dt);
        };

        m_draw = [metatable, gameState]()
        {
            metatable["draw"].call(gameState);
        };
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

    void draw() const
    {
        m_draw();
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
    std::function<void()> m_draw;
};

#endif
