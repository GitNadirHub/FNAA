#pragma once
#include <SFML/Graphics.hpp>
#include "camera.hpp"
void spawnDrink();

struct Drink
{
	Room* room;
	sf::Vector2f position;
	bool active = false;
};

extern int drinkCount;

extern Drink drinks[7];