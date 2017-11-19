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
    std::vector<Cell> m_cells;
    std::vector<Food> m_foods;
    sf::Clock         m_foodClock;
    sf::Clock         m_tickClock;
    bool              m_paused;
    bool              m_started;
    float             m_tickSeconds;
    float             m_foodSeconds;

 public:
    Program() noexcept;
    ~Program() noexcept;
    int run() noexcept;
};

#endif  // SRC_PROGRAM_HPP_
