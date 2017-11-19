// Copyright 2017 Beafantles

#ifndef SRC_CELL_HPP_
#define SRC_CELL_HPP_

#include <vector>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <constants.hpp>
#include <food.hpp>

class Cell : public sf::CircleShape
{
 private:
    float m_hp;
    float m_speed;  // Pixels per second
    bool  m_isDead;
    float m_xOffset;
    float m_yOffset;

    static float                                 noiseOffset;
    static std::uniform_real_distribution<float> radiusDistribution;

 public:
    Cell() noexcept;
    ~Cell() noexcept;
    void update(const float& _seconds) noexcept;
    void eat(std::vector<Food>* _foods) noexcept;
    bool is_dead() const noexcept;
};

#endif  // SRC_CELL_HPP_
