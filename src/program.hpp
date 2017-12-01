// Copyright 2017 Beafantles

#ifndef SRC_PROGRAM_HPP_
#define SRC_PROGRAM_HPP_

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <cell.hpp>
#include <food.hpp>

class Program
{
 private:
    sf::RenderWindow  m_window;
    sf::Font          m_font;
    sf::Text          m_timerText;
    sf::Text          m_timerSpeedMultiplierText;
    std::vector<Cell> m_cells;
    std::vector<Food> m_foods;
    sf::Clock         m_foodClock;
    sf::Clock         m_tickClock;
    sf::Clock         m_timer;
    bool              m_paused;
    bool              m_started;
    float             m_tickSeconds;
    float             m_foodSeconds;
    float             m_timerSeconds;
    float             m_timeSpeed;

 public:
    Program();  // Throws an exception if the font can't be loaded
    ~Program() noexcept = default;
    int run() noexcept;
};

#endif  // SRC_PROGRAM_HPP_
