#include <Game.hpp>
#include <thread>
#include <iostream>
//Modules
#include <Math.hpp>
#include <Graphics/Graphics.hpp>
#include <Audio/Audio.hpp>
#include <ECS/ECS.hpp>

Game::Game() :
    m_inputManager(m_window)
{

}

extern std::string lua_middleclass;

void Game::run()
{
    auto& state = Lua::getState();
    state.open_libraries();
    //Load middleclass
    state.script(lua_middleclass);
    //Expose
    state.set("window", &m_window);
    state.set("stateManager", &m_stateManager);
    
    if(!Graphics::init())
    {
        glfwTerminate();
        return;
    }
    
    /*if(!Audio::init())
    {
        Audio::destroy();
        return;
    }*/
    m_window.create(800, 600, "Zadymka", Window::Style::Windowed);

    //Register lua classes
    registerModules();
    //Load init script
    state.safe_script_file("init.lua");
    
    double dt = Lua::getState().get_or("dt", 1.0 / 20.0);
    double currentTime = glfwGetTime();
    double accumulator = 0.0;
    
    while(m_window.isOpen())
    {
        const double newTime = glfwGetTime();
        double frameTime = newTime - currentTime;
        if (frameTime > 0.25)
            frameTime = 0.25;

        currentTime = newTime;
        accumulator += frameTime;

        //Get current state
        const auto& currentState = m_stateManager.getCurrentState();

        if(glfwGetKey(m_window.getNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            m_window.close();

        //Update
        currentState.update(dt);
        //Fixed update
        while(accumulator >= dt)
        {
            currentState.fixedUpdate(dt);
            accumulator -= dt;
        }
        const double alpha = accumulator / dt;
        m_window.setCamera(currentState.getCamera());
        m_window.clear(0, 125, 125);
        currentState.draw(m_window, alpha);
        m_window.display();
        //Limit fps to 1000 so we can save some CPU cycles for other processes
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    glfwTerminate();
    //Audio::destroy();
}

void Game::registerModules()
{
    Math::registerModule();
    GameState::registerClass();
    StateManager::registerClass();
    Graphics::registerModule();
    Audio::registerModule();
    ECS::registerModule();
}
