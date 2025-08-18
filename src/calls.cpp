#include "game.hpp"
#include <SFML/Audio.hpp>
using namespace sf;

SoundBuffer buffCalls[4] = { SoundBuffer("res/snd/call1.wav"), //THEY BUFF
							 SoundBuffer("res/snd/call2.wav"),
							 SoundBuffer("res/snd/call3.wav"),
							 SoundBuffer("res/snd/call4.wav"), };
Sound sndCalls[4] = { Sound(buffCalls[0]), Sound(buffCalls[1]), Sound(buffCalls[2]), Sound(buffCalls[3]) };

void Game::handleCalls()
{
	int num = currentNight->num;
	if (num > 4) return;

	num--;

	if (!currentNight->callPlayed && sndCalls[num].getStatus() != Sound::Status::Playing)
	{
		sndCalls[num].play();
		currentNight->callPlayed = true;
	}
	
	if (currentState != GameState::Office && currentState != GameState::Camera)
	{
		sndCalls[num].stop();
		currentNight->callPlayed = false;
	}

}

