#include "animatronics.hpp"
#include "game.hpp"
#include "globals.hpp"
#include "camera.hpp"

using namespace sf;

FloweyStruct Flowey;
AsgoreStruct Asgore;
StarwalkerStruct Starwalker;

uint8_t floweyWaitTime = 5;

void FloweyStruct::update()
{
	float elapsed = Flowey.clock.getElapsedTime().asSeconds();

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
		Flowey.clock.restart();
		float randNum = randRange(0, 20);
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
			else if (location == &Garage)
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