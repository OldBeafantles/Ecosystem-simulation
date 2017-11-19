// Copyright 2017 Beafantles

#include <SFML/System/Vector2.hpp>
#include <constants.hpp>
#include <food.hpp>
#include <globals.hpp>

Food::Food() noexcept
  : sf::CircleShape{ FOOD_RADIUS, 8 }
  , m_hasBeenEaten{ false }
{
    this->setPosition(globals::X_DISTRIBUTION(globals::RANDOM_GENERATOR),
                      globals::Y_DISTRIBUTION(globals::RANDOM_GENERATOR));
    this->setOrigin(FOOD_RADIUS, FOOD_RADIUS);
    this->setFillColor(FOOD_COLOR);
    this->setOutlineThickness(FOOD_OUTLINE_THICKNESS);
    this->setOutlineColor(FOOD_OUTLINE_COLOR);
}

Food::~Food() {}

bool Food::has_been_eaten() const noexcept
{
    return m_hasBeenEaten;
}

void Food::set_has_been_eaten(bool _hasBeenEaten) noexcept
{
    m_hasBeenEaten = _hasBeenEaten;
}
