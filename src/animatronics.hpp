#pragma once
#include "camera.hpp"
#include <SFML/Graphics.hpp>
#include "globals.hpp"

struct AsgoreStruct {
	uint8_t AILEVEL = 20;
	Room* location = &Bedroom;
	sf::Clock clock;
	int consumed = 0;
	bool attackMode = false;
	sf::Clock attackClock;

	sf::Clock drinkClock;
	char drinkStage = '0';

	sf::Clock spawnClock;
	float spawnInterval = randRange(5, 20);

	void update();
	void reset();
};


struct StarwalkerStruct {
	uint8_t AILEVEL = 20;
	Room* location = &SWRoom;
	bool isFlashed = false;
	sf::Clock clock;


	Room* locationLast = location;
	bool lastFrameFlashed = false;

	void update();
	void reset();
};

struct FloweyStruct {
	uint8_t AILEVEL = 20;
	Room* location = &Bedroom;
	bool isFlashed = false;
	sf::Clock clock;
	sf::Clock totalClock;

	Room* locationLast = location;
	bool lastFrameFlashed = false;

	void update();
	void reset();
};

struct KnightStruct {
	uint8_t AILEVEL = 20;
	Room* location = &SWRoom;
	sf::Clock clock;
	void update();
	void reset();
};

extern FloweyStruct Flowey;
extern AsgoreStruct Asgore;
extern StarwalkerStruct Starwalker;
extern KnightStruct Knight;