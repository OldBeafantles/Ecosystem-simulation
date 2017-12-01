// Copyright 2017 Beafantles

#include <cmath>
#include <exception>
#include <random>
#include <string>
#include <vector>

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <SimplexNoise.h>
#include <cell.hpp>
#include <constants.hpp>
#include <food.hpp>
#include <globals.hpp>

std::uniform_real_distribution<float> Cell::radiusDistribution{ CELL_MIN_RADIUS, CELL_MAX_RADIUS };

float Cell::noiseOffset = 0.001f;

Cell::Cell() noexcept
  : sf::CircleShape{}
  , m_hp{ CELL_MAX_HP }
  , m_speed{}
  , m_isDead{ false }
  , m_xOffset{ Cell::noiseOffset }
  , m_yOffset{ Cell::noiseOffset + CELL_NOISE_OFFSET_INTERVAL }
{
    float radius = Cell::radiusDistribution(globals::RANDOM_GENERATOR);

    // Inits the graphical effects
    this->setOrigin(radius, radius);
    this->setRadius(radius);
    this->setPointCount(CELL_POINTS_COUNT);
    this->setFillColor(CELL_MAX_HP_COLOR);
    this->setOutlineColor(CELL_OUTLINE_COLOR);
    this->setOutlineThickness(CELL_OUTLINE_THICKNESS);

    // Inits the position of the cell
    float x = globals::X_DISTRIBUTION(globals::RANDOM_GENERATOR);
    float y = globals::Y_DISTRIBUTION(globals::RANDOM_GENERATOR);

    this->setPosition(x, y);

    // Inits the speed of the cell
    m_speed = CELL_MAX_SPEED
              - ((radius - CELL_MIN_RADIUS) / (CELL_MAX_RADIUS - CELL_MIN_RADIUS))
                  * (CELL_MAX_SPEED - CELL_MIN_SPEED);  // The biggest the cell
                                                        // is, the slowest speed
                                                        // it has

    Cell::noiseOffset += 2 * CELL_NOISE_OFFSET_INTERVAL;
}

Cell::~Cell() noexcept {}

void Cell::update(const float& _seconds) noexcept
{
    if (!m_isDead)
    {
        // Updates the position
        sf::Vector2<float> position = this->getPosition();
        float              x        = position.x;
        float              y        = position.y;

        // TODO(Beafantles): Random direction & check collisions & crack problem

        x = (SimplexNoise::noise(m_xOffset) + 1.0f) / 2.0f * WINDOW_WIDTH;
        y = (SimplexNoise::noise(m_yOffset) + 1.0f) / 2.0f * WINDOW_HEIGHT;
        m_xOffset += m_speed * _seconds / 100;
        m_yOffset += m_speed * _seconds / 100;

        this->setPosition(x, y);

        // Updates the HP & the color
        m_hp -= CELL_HP_LOST_PER_SECOND * (_seconds);
        if (m_hp <= 0.0f)
        {
            m_hp     = 0.0f;
            m_isDead = true;
        }

        sf::Color newColor(static_cast<sf::Uint8>(CELL_RED_VALUE_PER_HP * m_hp),
                           static_cast<sf::Uint8>(CELL_GREEN_VALUE_PER_HP * m_hp),
                           static_cast<sf::Uint8>(CELL_BLUE_VALUE_PER_HP * m_hp));

        this->setFillColor(newColor);
    }
}

bool Cell::is_dead() const noexcept
{
    return m_isDead;
}

void Cell::eat(std::vector<Food>* _foods) noexcept
{
    std::size_t nbFoods = _foods->size();
    for (std::size_t i = 0; i < nbFoods; i++)
    {
        const sf::Vector2<float> foodPosition = (_foods->begin() + i)->getPosition();
        const float              xFood        = foodPosition.x;
        const float              yFood        = foodPosition.y;
        const sf::Vector2<float> cellPosition = this->getPosition();
        const float              xCell        = cellPosition.x;
        const float              yCell        = cellPosition.y;
        float                    distance = std::sqrt(std::pow(xCell - xFood, 2.0f) + std::pow(yCell - yFood, 2.0f));
        if (distance < 0)
            distance *= -1;

        if (distance <= (this->getRadius() + FOOD_RADIUS))
        {
            m_hp += FOOD_HP_GAIN;
            if (m_hp > CELL_MAX_HP)
                m_hp = CELL_MAX_HP;
            _foods->erase(_foods->begin() + i);
            i--;
            nbFoods--;
        }
    }
}
