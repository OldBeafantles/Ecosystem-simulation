// Copyright 2017 Beafantles

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <constants.hpp>
#include <food.hpp>
#include <program.hpp>

Program::Program() noexcept
  : m_window{}
  , m_cells{}
  , m_foods{}
  , m_foodClock{}
  , m_tickClock{}
  , m_paused{ false }
  , m_started{ false }
  , m_tickSeconds{ 0.0f }
  , m_foodSeconds{ 0.0f }
{
    for (uint8_t i = 0; i < NB_CELLS_AT_THE_BEGINNING; i++)
    {
        m_cells.emplace_back();  // perfect forwading
    }
    m_foods.emplace_back();
    m_window.setFramerateLimit(WINDOW_MAX_FPS);
}

Program::~Program() noexcept {}

int Program::run() noexcept
{
    std::size_t nbCells;
    sf::Event   event;

    m_window.create(sf::VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT, 32 }, sf::String(WINDOW_TITLE), WINDOW_STYLE);

    while (m_window.isOpen())
    {
        while (m_window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed: m_window.close(); break;
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape: m_window.close(); break;
                        case sf::Keyboard::Space: m_paused = !m_paused; break;
                        case sf::Keyboard::Return:
                            if (!m_started)
                            {
                                m_started = true;
                                m_foodClock.restart();
                                m_tickClock.restart();
                            }
                            break;
                    }
                    break;
            }
        }

        m_window.clear();

        if (m_started)
        {
            for (const Food& food : m_foods)
                m_window.draw(food);

            for (const Cell& cell : m_cells)
                m_window.draw(cell);

            if (!m_paused)
            {
                m_foodSeconds += m_foodClock.getElapsedTime().asSeconds();
                m_tickSeconds += m_tickClock.getElapsedTime().asSeconds();

                nbCells = m_cells.size();
                for (std::size_t i = 0; i < nbCells; i++)
                {
                    m_cells[i].update(m_tickSeconds);
                    if (m_cells[i].is_dead())
                    {
                        m_cells.erase(m_cells.begin() + i);
                        i--;
                        nbCells--;
                    }
                    else
                        m_cells[i].eat(&m_foods);
                }

                if (m_foodSeconds >= FOOD_SPAWN_INTERVAL)
                {
                    m_foods.emplace_back();
                    m_foodSeconds = 0.0f;
                }

                m_tickClock.restart();
                m_foodClock.restart();
                m_tickSeconds = 0.0f;
            }
            else
            {
                m_foodClock.restart();
                m_tickClock.restart();
            }
        }

        m_window.display();
    }
    return 0;
}
