#pragma once
#include "game.hpp"
#include <SFML/Graphics.hpp>


extern GameState updateCamera();
extern void renderCamera(sf::RenderWindow& window);
struct Room;

extern Room Garage, Exterior, Shop, Bedroom, Hall, Garden, Bathroom, SWRoom, You;