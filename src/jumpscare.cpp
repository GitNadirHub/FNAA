#include "game.hpp"
#include "animator.hpp"
#include "resources.hpp"
#include <cmath>
#include "globals.hpp"
using namespace sf;

Texture t_floweyJumpscare("res/img/floweyJumpscare.png");
Sprite sprFloweyJumpscare(t_floweyJumpscare);

Clock animClock;

GameState floweyJumpscare(RenderWindow &window)
{
	static int lastIndex = 0;
	int index = 9;
	if (lastIndex<9)
		index = animateIndexed(10, 44, 44, 0.05f, animClock.getElapsedTime(), sprFloweyJumpscare);
	else
	{
		float shakeOffset = std::sin(animClock.getElapsedTime().asMilliseconds()) * 20.f;
		sprFloweyJumpscare.setPosition({ 720.f + shakeOffset, 800.f + shakeOffset/2.f});

	}

	float sizeOffset = sprFloweyJumpscare.getScale().x + 1 * deltaTime;

	sprFloweyJumpscare.setScale({ sizeOffset, sizeOffset });

	window.draw(sprFloweyJumpscare);
	if (index == 9 && animClock.getElapsedTime().asSeconds() > 2.f)
	{
		lastIndex = 0;
		return GameState::Death;
	}
	lastIndex = index;
	return GameState::Jumpscare;
}


Clock swClock;

SoundBuffer sndBfrSWSpeech("res/snd/starwalker.wav");
Sound sndSWSpeech(sndBfrSWSpeech);

GameState starwalkerJumpscare(RenderWindow& window)
{
	float elapsed = swClock.getElapsedTime().asSeconds();

    static Texture swTextures[7] =
	{
	Texture("res/img/sw1.png"), Texture("res/img/sw2.png"), Texture("res/img/sw3.png"), Texture("res/img/sw4.png"), Texture("res/img/sw5.png"), Texture("res/img/sw6.png"), Texture("res/img/sw7.png")
    };

    static Sprite sw[7] = {
        Sprite(swTextures[0]), Sprite(swTextures[1]), Sprite(swTextures[2]),
        Sprite(swTextures[3]), Sprite(swTextures[4]), Sprite(swTextures[5]),
        Sprite(swTextures[6])
    };

    if (elapsed < 3.8f)
	{
		window.draw(sw[0]);
	}
	else if (elapsed < 9.7f)
	{
		window.draw(sw[1]);
	}
	else if (elapsed < 12.f)
	{
		window.draw(sw[2]);
	}
	else if (elapsed < 17.f)
	{
		window.draw(sw[3]);
	}
	else if (elapsed < 21.f)
	{
		window.draw(sw[4]);
	}
	else if (elapsed < 27.f)
	{
		window.draw(sw[5]);
	}
	else if (elapsed < 30.f)
	{
		window.draw(sw[6]);
	}
	else
	{
		return GameState::Death;
	}
	return GameState::Jumpscare;
}

void floweyInit()
{
	sprFloweyJumpscare.setScale({ 15, 15 });
	sprFloweyJumpscare.setOrigin({ 20, 44 });
	sprFloweyJumpscare.setPosition({ 720, 800 });

	sndJumpscare.play();

}

void Game::jumpscare()
{
	animClock.restart();

	switch (jumpscareCulprit)
	{
	case 'F':
		floweyInit();
		break;
	case 'S':
		swClock.restart();
		sndSWSpeech.play();
		break;
	}

	while (currentState == GameState::Jumpscare)
	{

		deltaTime = deltaClock.restart().asSeconds();

		window.clear();
		window.draw(sprOffice);
		switch (jumpscareCulprit)
		{
		case 'F':
			currentState = floweyJumpscare(window);
			break;
		case 'S':
			currentState = starwalkerJumpscare(window);
			break;
		}
		window.display();
	}

}
