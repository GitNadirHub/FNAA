#include "game.hpp"
#include <SFML/Audio.hpp>
using namespace sf;

SoundBuffer buffCalls[3] = { SoundBuffer("res/snd/call1.wav"), //THEY BUFF
							 SoundBuffer("res/snd/call2.wav"),
							 SoundBuffer("res/snd/call3.wav"), };
Sound sndCalls[3] = {Sound(buffCalls[0]), Sound(buffCalls[1]), Sound(buffCalls[2])};

void Game::handleCalls()
{
	int num = currentNight->num;
	if (num > 5) return;

	num--;

	if (!currentNight->callPlayed && sndCalls[num].getStatus() != Sound::Status::Playing)
	{
		sndCalls[num].play();
		currentNight->callPlayed = true;
	}
}

