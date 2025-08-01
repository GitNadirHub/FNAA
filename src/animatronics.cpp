#include "animatronics.hpp"
#include "game.hpp"
#include "globals.hpp"
#include "camera.hpp"
#include "drink.hpp"
#include "resources.hpp"
#include <iostream>

using namespace sf;

FloweyStruct Flowey;
AsgoreStruct Asgore;
StarwalkerStruct Starwalker;

uint8_t floweyWaitTime = 5;
uint8_t starwalkerWaitTime = 5;
uint8_t asgoreWaitTime = 5;

void FloweyStruct::update()
{
	float elapsed = clock.getElapsedTime().asSeconds();

	static Room* locationLast = location;
	static bool lastFrameFlashed = false;


	if (location == &You)
	{
		static Clock totalClock;
		if (!totalClock.isRunning())
			totalClock.restart();
		float totalElapsed = totalClock.getElapsedTime().asSeconds();
		if (totalElapsed>=30.f) //this is for if the player flashes repeatedly to cheese stuff
		{
			game.currentState = GameState::Jumpscare;
			game.jumpscareCulprit = 'F';
			location = &Bedroom;
			totalClock.reset();
			return;
		}
		auto handleDoor = [&](bool& doorFlag)
			{
				if (isFlashed)
				{
					if (!lastFrameFlashed)
					{
						lastFrameFlashed = true;
						clock.restart();
						elapsed = 0.f;
						return;
					}
					if (elapsed >= 3.f)
					{
						location = &Bedroom;
						doorFlag = false;
						lastFrameFlashed = false;
						clock.restart();
						totalClock.reset();
						return;
					}
				}
				else
					lastFrameFlashed = false;

				if (locationLast != location)
				{
					clock.restart();
					elapsed = 0.f;
					locationLast = location;
				}
				if (elapsed >= 15.f)
				{
					game.currentState = GameState::Jumpscare;
					game.jumpscareCulprit = 'F';
					location = &Bedroom;
				}
			};

		if (floweySmallDoor)
			handleDoor(floweySmallDoor);
		else if (floweyBigDoor)
			handleDoor(floweyBigDoor);

		return;
	}


	if (elapsed >= floweyWaitTime)
	{
		clock.restart();
		float randNum = randRange(1, 20);
		floweyWaitTime = randRange(5, 10);
		if (AILEVEL >= randNum)
		{
			if (location == &Bedroom)
			{
				if (randRange(0, 1) == 0)
				{
					location = &You;
					floweySmallDoor = true;
				}
				else
				{
					location = &Shop;
				}
			}
			else if (location == &Shop)
			{
				location = &Exterior;
			}
			else if (location == &Exterior)
			{
				location = &Garage;
			}
			else if (location == &Garage && !starwalkerBigDoor)
			{
				location = &You;
				floweyBigDoor = true;
			}
		}
	}
	locationLast = location;
}

void FloweyStruct::reset()
{
	location = &Bedroom;
	floweyWaitTime = 5;
	clock.restart();
	floweySmallDoor = false;
	floweyBigDoor = false;
}

Room* SWRandRoom()
{
	if (randRange(0, 1) == 0)
		return &SWRoom;

	std::vector<Room*> possibleRooms = { &Bathroom, &Garden, &Hall, &Bedroom, &Shop, &Exterior, &Garage };
	return possibleRooms[rand() % possibleRooms.size()];
}

void StarwalkerStruct::update()
{
	float elapsed = clock.getElapsedTime().asSeconds();

	static Room* locationLast = location;
	static bool lastFrameFlashed = false;

	if (location == &You)
	{
		if (starwalkerBigDoor)
		{
			static Clock totalClock;
			if (!totalClock.isRunning())
				totalClock.restart();
			float totalElapsed = totalClock.getElapsedTime().asSeconds();
			if (totalElapsed >= 30.f)
			{
				game.currentState = GameState::Jumpscare;
				game.jumpscareCulprit = 'S';
				location = &Bedroom;
				totalClock.reset();
				return;
			}


			if (isFlashed)
			{
				if (!lastFrameFlashed)
				{
					lastFrameFlashed = true;
					clock.restart();
					elapsed = 0.f;
				}
				else if (elapsed >= 3.f)
				{
					location = SWRandRoom(); // 50% SWRoom, 50% random
					starwalkerBigDoor = false;
					lastFrameFlashed = false;
					clock.restart();
					totalClock.reset();
				}
			}
			else
			{
				lastFrameFlashed = false;
			}

			if (locationLast != location)
			{
				clock.restart();
				elapsed = 0.f;
				locationLast = location;
			}

			if (elapsed >= 15.f)
			{
				game.currentState = GameState::Jumpscare;
				game.jumpscareCulprit = 'S';
				location = &Bedroom;
			}
		}
	}

	if (elapsed >= starwalkerWaitTime)
	{
		clock.restart();
		float randNum = randRange(1, 20);
		starwalkerWaitTime = randRange(2, 5);
		if (AILEVEL >= randNum)
		{
			if (location == &SWRoom)
			{
				location = &Bathroom;
			}
			else if (location == &Bathroom)
			{
				location = &Garden;
			}
			else if (location == &Garden)
			{
				location = &Hall;
			}
			else if (location == &Hall)
			{
				location = &Bedroom;
			}
			else if (location == &Bedroom)
			{
				location = &Shop;
			}
			else if (location == &Shop)
			{
				location = &Exterior;
			}
			else if (location == &Exterior)
			{
				location = &Garage;
			}
			else if (location == &Garage)
			{
				location = &You;
				starwalkerBigDoor = true;
			}
		}
	}
	locationLast = location;
}

void StarwalkerStruct::reset()
{
	location = &SWRoom;
	starwalkerWaitTime = 5;
	clock.restart();
	starwalkerBigDoor = false;
}

void AsgoreStruct::update()
{
    float elapsed = clock.getElapsedTime().asSeconds();

    static Room* possibleRooms[7] = { &Bedroom, &Shop, &Hall, &Garden, &Bathroom, &Exterior, &Garage };

	static bool attackMode = false;

	static Clock attackClock;

	if (attackMode)
	{
		float elapsedAttack = attackClock.getElapsedTime().asSeconds();
		if (elapsedAttack > 2.314159265358979323f)
		{
			attackClock.restart();
			if (location == &Bathroom)
			{
				location = &Garden;
			}
			else if (location == &Garden)
			{
				location = &Hall;
			}
			else if (location == &Hall)
			{
				location = &Bedroom;
			}
			else if (location == &Bedroom)
			{
				location = &Shop;
			}
			else if (location == &Shop)
			{
				location = &Exterior;
			}
			else if (location == &Exterior)
			{
				location = &Garage;
			}
			else if (location == &Garage && sndSeven.getStatus()!=Sound::Status::Playing)
			{
				game.currentState = GameState::Jumpscare;
			}
		}
		return;
	}

	if (drinkCount >= 7)
	{
		Flowey.AILEVEL = 0;
		Starwalker.AILEVEL = 0;
		Flowey.location = &Bathroom;
		Starwalker.location = &SWRoom;
		attackMode = true;
		sndSeven.play();
		attackClock.restart();
		return;
	}

    static Clock drinkClock;
    static char drinkStage = '0';
    if (drinkStage == '1')
    {
        if (drinkClock.getElapsedTime().asSeconds() < 5.f)
            return;
        drinkStage = '2';
    }

    static Clock spawnClock;
    static float spawnInterval = randRange(5, 20);
    if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval)
    {
        spawnDrink();
        spawnClock.restart();
        spawnInterval = randRange(3, 10);
    }

    auto ID = location->id;

    int minDistance = 99;
    int minID = ID;
    Drink* target = nullptr;
    for (auto& drink : drinks)
    {
        if (drink.active && drink.room)
        {
            int drinkID = drink.room->id;
            int distance = std::abs(ID - drinkID);
            if (distance < minDistance)
            {
                minDistance = distance;
                minID = drinkID;
                target = &drink;
            }
        }
    }

    if (minID == ID)
    {
        if (drinkStage == '2')
        {
			if (target != nullptr)
			{
				consumed++;
				target->active = false;
				drinkCount--;
			}
            drinkStage = '0';
            return;
        }
        else if (drinkStage == '0')
        {
            drinkStage = '1';
            drinkClock.restart();
        }
    }
    else
    {
        drinkStage = '0';
    }

    if (elapsed > asgoreWaitTime)
    {
        asgoreWaitTime = randRange(2, 5);
        clock.restart();
        int randNum = randRange(1, 20);
        if (AILEVEL >= randNum)
        {
            if (minID < ID)
            {
                for (int i = 0; i < 7; i++)
                {
                    if (possibleRooms[i]->id == ID - 1)
                    {
                        location = possibleRooms[i];
                        return;
                    }
                }
            }
            else if (minID > ID)
            {
                for (int i = 0; i < 7; i++)
                {
                    if (possibleRooms[i]->id == ID + 1)
                    {
                        location = possibleRooms[i];
                        return;
                    }
                }
            }
        }
    }
}
