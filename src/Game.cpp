#include <Game.hpp>
#include <SFML/Window/Event.hpp>
#include <thread>
#include <iostream>

Game::Game() :
    m_inputManager(m_window)
{

}
#include <Graphics/Sprite.hpp>

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

    if(!glfwInit())
    {
        std::cerr << "Failed to load glfw. Aborting\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window.create(800, 600, "Zadymka", Window::Style::Windowed);

    //Register lua classes
    registerClasses();
    //Load init script
    state.safe_script_file("init.lua");

    //Frame time counter
    double lastTime = glfwGetTime();
    int framesCount = 0;

    double dt = Lua::getState().get_or("dt", 1.0 / 20.0);
    double currentTime = glfwGetTime();
    double accumulator = 0.0;

    while(m_window.isOpen())
    {
        const double newTime = glfwGetTime();

        ++framesCount;
        if(newTime - lastTime >= 1.0)
        {
            std::cerr << 1000.0/double(framesCount) << " ms/frame - " << framesCount << '\n';
            framesCount = 0;
            lastTime += 1.0;
        }

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
}

#include <ECS/EntityManager.hpp>
#include <ECS/SystemManager.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Rectangle.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/RenderTexture.hpp>
#include <Graphics/VertexArray.hpp>

void Game::registerClasses()
{
    //Core
    StateManager::registerClass();
    Window::registerClass();
    //Graphics
    Camera::registerClass();
    Texture::registerClass();
    Shader::registerClass();
    Rectangle::registerClass();
    Sprite::registerClass();
    Font::registerClass();
    Text::registerClass();
    RenderTexture::registerClass();
    VertexArray::registerClass();
    //ECS
    Entity::registerClass();
    EventManager::registerClass();
    EntityManager::registerClass();
    SystemManager::registerClass();
    System::registerClass();
}
