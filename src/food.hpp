// Copyright 2017 Beafantles

#ifndef SRC_FOOD_HPP_
#define SRC_FOOD_HPP_

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Food : public sf::CircleShape
{
 private:
    bool m_hasBeenEaten;

 public:
    Food() noexcept;
    ~Food() noexcept;
    bool has_been_eaten() const noexcept;
    void set_has_been_eaten(bool _hasBeenEaten) noexcept;
};

#endif  // SRC_FOOD_HPP_
