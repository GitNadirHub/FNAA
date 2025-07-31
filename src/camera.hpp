#pragma once
#include "game.hpp"
#include <SFML/Graphics.hpp>


extern GameState updateCamera();
extern void renderCamera(sf::RenderWindow& window);
struct Room
{
	uint8_t occupants = 0;

	int id; //for Asgore pathfinding

	Room(int id) : id(id) {}

	void calculateOccupants();
};

extern Room Garage, Exterior, Shop, Bedroom, Hall, Garden, Bathroom, SWRoom, You;