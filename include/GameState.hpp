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
        m_update = [](float){};
        m_fixedUpdate = [](float){};
        m_draw = [](){};
    }

    GameState(sol::object gameState)
    {
        sol::userdata ud = gameState;
        sol::table metatable = ud[sol::metatable_key];
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

    void update(float dt)
    {
        m_update(dt);
    }

    void fixedUpdate(float dt)
    {
        m_fixedUpdate(dt);
    }

    void draw()
    {
        m_draw();
    }
protected:
    std::function<void(float)> m_update;
    std::function<void(float)> m_fixedUpdate;
    std::function<void()> m_draw;
};

#endif
