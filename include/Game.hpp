#ifndef GAME_HPP
#define GAME_HPP
#include <Graphics/Window.hpp>
#include <StateManager.hpp>
#include <InputManager.hpp>


class Game
{
public:
    Game() = default;
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;
    ~Game() = default;
    void run();
protected:
    Window m_window;
    StateManager m_stateManager;
    InputManager m_inputManager;

    void registerClasses();
};

#endif
