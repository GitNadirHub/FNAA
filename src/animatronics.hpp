#pragma once
#include "camera.hpp"
#include <SFML/Graphics.hpp>

struct AsgoreStruct {
	uint8_t AILEVEL = 20;
	Room* location = &Bedroom;
	sf::Clock clock;
	int consumed = 0;
	void update();
};
struct StarwalkerStruct {
	uint8_t AILEVEL = 20;
	Room* location = &SWRoom;
	bool isFlashed = false;
	sf::Clock clock;
	void update();
	void reset();
};

struct FloweyStruct {
	uint8_t AILEVEL = 20;
	Room* location = &Bedroom;
	bool isFlashed = false;
	sf::Clock clock;
	void update();
	void reset();
};

extern FloweyStruct Flowey;
extern AsgoreStruct Asgore;
extern StarwalkerStruct Starwalker;
