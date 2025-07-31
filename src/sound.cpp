#include <sfml/Audio.hpp>
#include "resources.hpp"
#include "globals.hpp"
using namespace sf;

Clock ambienceClock;

int ambienceTime = 0;

void ambienceSound()
{
	float elapsed = ambienceClock.getElapsedTime().asSeconds();
	if (elapsed < ambienceTime)
		return;
	ambienceClock.restart();
	ambienceTime = randRange(10, 30);

	int id = randRange(0, 0);
	static Sound sounds[1] = { sndEerie };
	sounds[id].play();
}
