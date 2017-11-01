#include <Game.hpp>
#include <SFML/Window/Event.hpp>

Game::Game()
    :
      m_window()
{

}

struct lul
{
    int a;
};

#include <iostream>

void Game::run()
{
    auto& state = Lua::getState();
    state.open_libraries();
    state.set("window", &m_window);
    //Load init script
    state.safe_script_file("init.lua");
    const unsigned int width = state.get_or("window_width", 800);
    const unsigned int height = state.get_or("window_height", 600);
    const std::string title = state.get_or("window_title", std::string("Zadymka"));
    m_window.create(sf::VideoMode(width, height, sf::VideoMode::getDesktopMode().bitsPerPixel),
                    title,
                    sf::Style::None);
    while(m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }
        //Update


        //Fixed update


        //Interpolation

        m_window.clear();
        //Render
        m_window.display();
    }
}
