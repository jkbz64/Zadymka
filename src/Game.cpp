#include <Game.hpp>
#include <SFML/Window/Event.hpp>
#include <thread>

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
    m_window.create(sf::VideoMode(800, 600, sf::VideoMode::getDesktopMode().bitsPerPixel),
                    "Zadymka",
                    sf::Style::Default);
    m_window.setVerticalSyncEnabled(true);
    //Register lua classes
    registerClasses();
    //Load init script
    state.safe_script_file("init.lua");

    sf::Clock clock;
    float dt = Lua::getState().get_or("dt", 1.f / 20.f);

    float currentTime = clock.getElapsedTime().asSeconds();
    float accumulator = 0.f;

    while(m_window.isOpen())
    {
        const float newTime = clock.getElapsedTime().asSeconds();
        float frameTime = newTime - currentTime;
        if (frameTime > 0.25f)
            frameTime = 0.25f;
        currentTime = newTime;
        accumulator += frameTime;
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
            m_inputManager.update(event);
        }
        const auto& currentState = m_stateManager.getCurrentState();
        //Update logic
        currentState.update(dt);
        //Fixed update
        while(accumulator >= dt)
        {
            currentState.fixedUpdate(dt);
            accumulator -= dt;
        }
        const float alpha = accumulator / dt;
        m_window.setView(currentState.getCamera());
        //Clear screen
        m_window.clear(sf::Color(0, 125, 125));
        //Render
        currentState.draw(m_window, alpha);
        m_window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

#include <ECS/EntityManager.hpp>
#include <ECS/SystemManager.hpp>

extern std::string lua_gameState;

void Game::registerClasses()
{
    Camera::registerClass();
    StateManager::registerClass();
    InputManager::registerClass();
    Window::registerClass();
    Entity::registerClass();
    EventManager::registerClass();
    EntityManager::registerClass();
    SystemManager::registerClass();
    System::registerClass();
}
