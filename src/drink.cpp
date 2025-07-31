#include "drink.hpp"
#include "game.hpp"
#include "globals.hpp"
#include "camera.hpp"
#include <vector>
#include <cmath>
#include "animatronics.hpp"

using namespace sf;

int drinkCount = 7;

Drink drinks[7];

Room* getRandomRoom()
{
	//return &Bedroom; //debug
	// choose randomly from Exterior, Shop, Bedroom, Hall, Garden, Bathroom
	static Room* possibleRooms[6] = {&Exterior, &Shop, &Bedroom, &Hall, &Garden, &Bathroom};

	if (!Asgore.location)
		return possibleRooms[randRange(0, 6)];

	std::vector<Room*> farAwayRooms;
	for (int i = 0; i < 6; i++)
	{
		auto id = possibleRooms[i]->id;
		auto asgoreID = Asgore.location->id;
		if (std::abs(id - asgoreID) > 1)
			farAwayRooms.push_back(possibleRooms[i]);
	}

	int index = randRange(0, farAwayRooms.size()-1);
	return farAwayRooms[index];
}

void spawnDrink()
{
	if (drinkCount >= 7) return; 
	drinkCount++;
	int newDrinkIndex = 0;
	for (int i = 0; i < 7; i++)
	{
		if (!drinks[i].active)
			newDrinkIndex = i;
	}
	drinks[newDrinkIndex].room = getRandomRoom();
	drinks[newDrinkIndex].position = Vector2f(randRange(100, 800), randRange(100, 500));
	drinks[newDrinkIndex].active = true;
}