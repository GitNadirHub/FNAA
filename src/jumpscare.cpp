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

Texture t("res/img/truck.png");
Sprite truck(t);

void asgoreInit()
{
	sndBeep.play(); 
	truck.setPosition({ 695, 377 });
	truck.setOrigin({ 211, 213 });
}

GameState asgoreJumpscare(RenderWindow& window)
{
	static float scrollSpeed = 1000.f;
	Vector2i mousePos = Mouse::getPosition();
	Vector2f mousePosF = { mousePos.x * 1.f, mousePos.y * 1.f };
	if (mousePos.x < 400)
	{
		Vector2f pos = sprOffice.getPosition();
		pos.x = std::min(pos.x + scrollSpeed * deltaTime, 0.f);
		sprOffice.setPosition(pos);
	}
	else if (mousePos.x > SCREEN_WIDTH - 400)
	{
		Vector2f pos = sprOffice.getPosition();
		pos.x = std::max(pos.x - scrollSpeed * deltaTime, SCREEN_WIDTH - 1600.f);
		sprOffice.setPosition(pos);
	}

	Vector2f camOffset = sprOffice.getPosition(); // The current camera scroll thingy offset whatever uhhhhhh yeah i guess well this is the camera offset sooo that's it i guess so i hope u got the point like yes ofc this is the camera offset in case u didnt get the point of this comment yet. Anyway, this is the current camera scroll thingy offset whatever uhhhhhh yeah i guess well this is the camera offset sooo that's it i guess so i hope u got the point like yes ofc this is the camera offset 
	rectPoint cameraBounds({ 1115.f + camOffset.x, 383.f + camOffset.y }, { 1383.f + camOffset.x, 607.f + camOffset.y });

	Vector2f p = Vector2f({ 695, 577 }) + camOffset; //ive never written worse code before but im about to fall asleep

	truck.setPosition(p);

	float scale = sndBeep.getPlayingOffset().asSeconds();

	truck.setScale({ scale, scale });
	if (sndBeep.getStatus() != Sound::Status::Playing) return GameState::Death;

	window.draw(sprOffice);
	window.draw(truck);

	return GameState::Jumpscare;
}

void Game::jumpscare()
{
	animClock.restart();

	sndBuzz.stop();
	sndFnaf2Hall.stop();
	sndIntercepted.stop();
	sndStatic.stop();

	switch (jumpscareCulprit)
	{
	case 'F':
		floweyInit();
		break;
	case 'S':
		swClock.restart();
		sndSWSpeech.play();
		break;
	case 'A':
		asgoreInit();
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
		case 'A':
			currentState = asgoreJumpscare(window);
		}
		window.display();
	}

}
