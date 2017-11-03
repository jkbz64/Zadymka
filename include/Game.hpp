#ifndef GAME_HPP
#define GAME_HPP
#include <Window.hpp>
#include <StateManager.hpp>

class Game
{
public:
    Game();
    void run();
protected:
    Window m_window;
    StateManager m_stateManager;

    void registerClasses();
};

#endif
