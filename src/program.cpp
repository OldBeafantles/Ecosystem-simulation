// Copyright 2017 Beafantles

#include <iostream>
#include <sstream>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <constants.hpp>
#include <food.hpp>
#include <program.hpp>
#include <utils.hpp>

Program::Program()
  : m_window{}
  , m_font{}
  , m_cells{}
  , m_foods{}
  , m_foodClock{}
  , m_tickClock{}
  , m_timer{}
  , m_timerText{}
  , m_timerSpeedMultiplierText{}
  , m_paused{ false }
  , m_started{ false }
  , m_tickSeconds{ 0.0f }
  , m_foodSeconds{ 0.0f }
  , m_timerSeconds{ 0.0f }
  , m_timeSpeed{ 1 }
{
    for (uint8_t i = 0; i < NB_CELLS_AT_THE_BEGINNING; i++)
    {
        m_cells.emplace_back();  // perfect forwading
    }
    m_foods.emplace_back();
    m_window.setFramerateLimit(WINDOW_MAX_FPS);
    if (!m_font.loadFromFile(FONT_PATH))
    {
        std::cerr << "Couldn't load " + static_cast<std::string>(FONT_PATH) + ".\nExiting...\n";
        exit(EXIT_FAILURE);
    }
    m_timerText.setFont(m_font);
    m_timerText.setCharacterSize(TIMER_TEXT_SIZE);
    m_timerText.setFillColor(TIMER_TEXT_COLOR);
    m_timerText.setString("00:00:00.000");
    m_timerText.setPosition(0, 0);
    m_timerSpeedMultiplierText.setFont(m_font);
    m_timerSpeedMultiplierText.setCharacterSize(TIMER_MULTIPLIER_TEXT_SIZE);
    m_timerSpeedMultiplierText.setFillColor(TIMER_MULTIPLIER_TEXT_COLOR);
    m_timerSpeedMultiplierText.setString("x" + std::to_string(m_timeSpeed));
    m_timerSpeedMultiplierText.setPosition(0, WINDOW_HEIGHT - TIMER_MULTIPLIER_TEXT_SIZE - 5);
}

int Program::run() noexcept
{
    std::size_t nbCells;
    sf::Event   event;

    m_window.create(sf::VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT, 32 }, sf::String(WINDOW_TITLE), WINDOW_STYLE);
    m_window.setPosition({ WINDOW_X_POSITION, WINDOW_Y_POSITION });

    while (m_window.isOpen())
    {
        while (m_window.pollEvent(event))
        {
            std::ostringstream str;
            switch (event.type)
            {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            m_window.close();
                            break;
                        case sf::Keyboard::Space:
                            m_paused = !m_paused;
                            break;
                        case sf::Keyboard::Return:
                            if (!m_started)
                            {
                                m_started = true;
                                m_foodClock.restart();
                                m_tickClock.restart();
                                m_timer.restart();
                            }
                            break;
                        case sf::Keyboard::Right:
                            m_timeSpeed *= 2;
                            str << m_timeSpeed;
                            m_timerSpeedMultiplierText.setString("x" + str.str());
                            break;
                        case sf::Keyboard::Left:
                            m_timeSpeed /= 2;
                            str << m_timeSpeed;
                            m_timerSpeedMultiplierText.setString("x" + str.str());
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

            m_window.draw(m_timerText);

            if (m_timeSpeed != 1.0f)
                m_window.draw(m_timerSpeedMultiplierText);

            if (!m_paused)
            {
                m_foodSeconds += m_foodClock.getElapsedTime().asSeconds() * m_timeSpeed;
                m_tickSeconds += m_tickClock.getElapsedTime().asSeconds() * m_timeSpeed;
                m_timerSeconds += m_timer.getElapsedTime().asSeconds() * m_timeSpeed;
                m_timerText.setString(utils::convert_time_to_str(m_timerSeconds));

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
                m_timer.restart();
                m_tickSeconds = 0.0f;
            }
            else
            {
                m_foodClock.restart();
                m_tickClock.restart();
                m_timer.restart();
            }
        }

        m_window.display();
    }
    return 0;
}
