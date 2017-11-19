// Copyright 2017 Beafantles

#ifndef SRC_GLOBALS_HPP_
#define SRC_GLOBALS_HPP_

#include <random>

#include <constants.hpp>

namespace globals
{
static std::default_random_engine              RANDOM_GENERATOR;
static std::uniform_int_distribution<uint16_t> X_DISTRIBUTION{ 100, WINDOW_WIDTH - 100 };
static std::uniform_int_distribution<uint16_t> Y_DISTRIBUTION{ 100, WINDOW_HEIGHT - 100 };
}  // namespace globals
#endif  // SRC_GLOBALS_HPP_
