// Copyright 2017 Beafantles

#ifndef SRC_CONSTANTS_HPP_
#define SRC_CONSTANTS_HPP_

#include <cstdint>
#include <random>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

constexpr float PI = 3.14f;  // Don't touch it

// Simulation window constants
const uint16_t    WINDOW_WIDTH      = sf::VideoMode::getDesktopMode().width - 200;
const uint16_t    WINDOW_HEIGHT     = WINDOW_WIDTH * 9 / 16;
const uint16_t    WINDOW_X_POSITION = 100;
const uint16_t    WINDOW_Y_POSITION = (sf::VideoMode::getDesktopMode().height - WINDOW_HEIGHT) / 2;
constexpr char    WINDOW_TITLE[]    = "Ecosystem simulation";
constexpr uint8_t WINDOW_STYLE      = sf::Style::None;
constexpr uint8_t WINDOW_MAX_FPS    = 60;

// Font & text settings
const char        FONT_PATH[]      = "../UbuntuMono-B.ttf";        // The path to the font (relative to the executable)
constexpr uint8_t TIMER_TEXT_SIZE  = 34;                           // The size of the text for the timer
const sf::Color   TIMER_TEXT_COLOR = sf::Color::White;             // The color of the text for the timer
constexpr uint8_t TIMER_MULTIPLIER_TEXT_SIZE  = 30;                // The size of the text for the speed multiplier
const sf::Color   TIMER_MULTIPLIER_TEXT_COLOR = sf::Color::White;  // The color of the text for the speed multiplier

// Cell constants
constexpr float       CELL_MAX_HP       = 100.f;  // The max HP of the cell
constexpr std::size_t CELL_POINTS_COUNT = 50;     // 3 = triangle
                                                  // 4 = square
                                                  // 8 = octagon
                                                  // The highest this value is, the most
                                                  // "circular" the cell gonna look like

constexpr float   CELL_OUTLINE_THICKNESS     = 2.f;   // The thickness of the membranes of the cells
constexpr float   CELL_MIN_RADIUS            = 5;     // The minimal value for the radius of the cells
constexpr float   CELL_MAX_RADIUS            = 50;    // The maximal value for the radius of the cells
constexpr uint8_t CELL_HP_LOST_PER_SECOND    = 3;     // The amount of HP each cell loses per second
constexpr uint8_t CELL_MAX_SPEED             = 50;    // The maximal speed of the cells (pixels/second)
constexpr uint8_t CELL_MIN_SPEED             = 10;    // The minimal speed of the cells (pixels/second)
constexpr float   CELL_NOISE_OFFSET_INTERVAL = 3.0f;  // The value of the interval of the offset between two
                                                    // different cells (choosing an integer will make the cells centered
                                                    // at the beginning of the animation, as the simplex noise frequency
                                                    // is equals to 1)

const sf::Color CELL_MAX_HP_COLOR  = sf::Color::Green;  // The color of the cells when they're full HP
const sf::Color CELL_MIN_HP_COLOR  = sf::Color::Red;    // The color of the cells when they're almost-dead
const sf::Color CELL_OUTLINE_COLOR = sf::Color::White;  // The color of the membrane of the cells

constexpr uint8_t NB_CELLS_AT_THE_BEGINNING = 30;  // The number of cells spawning at the beginning of the simulation

const float CELL_RED_VALUE_PER_HP   = (CELL_MAX_HP_COLOR.r - CELL_MIN_HP_COLOR.r) / CELL_MAX_HP;  // Don't touch this
const float CELL_GREEN_VALUE_PER_HP = (CELL_MAX_HP_COLOR.g - CELL_MIN_HP_COLOR.g) / CELL_MAX_HP;  // Don't touch this
const float CELL_BLUE_VALUE_PER_HP  = (CELL_MAX_HP_COLOR.b - CELL_MIN_HP_COLOR.b) / CELL_MAX_HP;  // Don't touch this

// Food constants
constexpr float FOOD_HP_GAIN        = 20.0f;  // The number of HP the cells regain by eating food
constexpr float FOOD_RADIUS         = 10.0f;  // The radius value of the food
constexpr float FOOD_SPAWN_INTERVAL = 0.7f;   // The interval between the spawn of two different piles of food (in
                                              // seconds)
const sf::Color FOOD_COLOR             = sf::Color::Blue;   // The color of food
const sf::Color FOOD_OUTLINE_COLOR     = sf::Color::White;  // The color of the food "membranes"
constexpr float FOOD_OUTLINE_THICKNESS = 2.0f;              // Food membranes thickness

#endif  // SRC_CONSTANTS_HPP_
