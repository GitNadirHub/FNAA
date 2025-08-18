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

	int id = randRange(0, 8);
    static sf::Sound sounds[] = {
       sndEerie,
        sndCave,
        sndLaugh,
        sndCave2,
        sndCave3,
        sndGrass,
        sndStep,
        sndSpamton,
        sndFleeFlee
    };
	sounds[id].play();
}
