#pragma once
#include <SFML/Graphics.hpp>
#include "resources.hpp"

extern int hour;
extern sf::Clock hourTimer;

void initTimer(), updateTimer(sf::RenderWindow &window);

extern sf::Text hourText;
