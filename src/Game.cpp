#include <Game.hpp>
#include <SFML/Window/Event.hpp>

Game::Game()
    :
      m_window()
{

}

void Game::run()
{
    Lua::getState().open_libraries();
    m_window.create(sf::VideoMode(800, 600), "Zadymka", sf::Style::Default);
    while(m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

        m_window.clear();
        m_window.display();
    }
}
