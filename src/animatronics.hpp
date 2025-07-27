#pragma once
#include "camera.hpp"
#include <SFML/Graphics.hpp>

struct AsgoreStruct {
	uint8_t AILEVEL = 0;
	Room* location = &Bedroom;
	void update()
	{

	}
};
struct StarwalkerStruct {
	uint8_t AILEVEL = 0;
	Room* location = &SWRoom;
	void update()
	{

	}
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
