#include <Game.hpp>
#include <SFML/Window/Event.hpp>
#include <thread>

Game::Game()
    :
      m_window()
{

}

void Game::run()
{
    auto& state = Lua::getState();
    state.open_libraries();
    //Load middleclass
    state.require_file("class", "lib/middleclass.lua");
    //Expose
    state.set("window", &m_window);
    state.set("stateManager", &m_stateManager);

    m_window.create(sf::VideoMode(800, 600, sf::VideoMode::getDesktopMode().bitsPerPixel),
                    "Zadymka",
                    sf::Style::Default);

    Camera::exposeToLua();
    //Load init script
    state.safe_script_file("init.lua");

    sf::Clock clock;
    const float dt = 1.0 / 10.0;

    float currentTime = clock.getElapsedTime().asSeconds();
    float accumulator = 0.f;

    while(m_window.isOpen())
    {
        float newTime = clock.getElapsedTime().asSeconds();
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
        }

        const auto& currentState = m_stateManager.getCurrentState();
        //Update logic
        currentState.update(dt);

        //Fixed update
        while(accumulator >= dt)
        {
            //Save previous state - TODO
            currentState.fixedUpdate(dt);
            accumulator -= dt;
        }
        //Interpolation - TODO
        const float alpha = accumulator / dt;

        m_window.setView(currentState.getView());
        //Clear screen
        m_window.clear(sf::Color(0, 125, 125));
        //Render
        currentState.draw();
        m_window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
