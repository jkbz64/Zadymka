#ifndef GAME_HPP
#define GAME_HPP
#include <Window.hpp>
#include <StateManager.hpp>
#include <InputManager.hpp>

class Game
{
public:
    Game();
    void run();
protected:
    Window m_window;
    StateManager m_stateManager;
    InputManager m_inputManager;

    void registerClasses();
};

#endif
