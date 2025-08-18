#include "game.hpp"
#include "globals.hpp"
#include "resources.hpp"
#include "camera.hpp"
#include "animatronics.hpp"
#include "timer.hpp"
#include "quitting.hpp"
//#include "jumpscare.hpp"

using namespace sf;

Shader vignette;
Shader vignetteStrong;
Shader bloom;
Shader halo;


//Night		night1(20, 20, 20, 20, 1),
Night		night1(3, 0, 1, 0, 1),
			night2(5, 2, 0, 0, 2),
			night3(7, 3, 5, 2, 3),
			night4(10, 5, 10, 7, 4),
			night5(10, 5, 10, 10, 5),
			night6(20, 10, 15, 15, 6);

void initializeOffice()
{
	sprOffice.setPosition({ -170.f, 0.f });
	initTimer();
}

void Night::initNight()
{
	Asgore.AILEVEL = AILEVELS[0];
	Flowey.AILEVEL = AILEVELS[1];
	Starwalker.AILEVEL = AILEVELS[2];
	Knight.AILEVEL = AILEVELS[3];
}

void startNight(RenderWindow &window)
{
	initializeOffice();

	game.currentNight->initNight();

	int num = game.currentNight->num;

	std::string title = "Night " + std::to_string(num) + "\n 12 AM";
	Text introText(font);
	introText.setString(title);
	introText.setPosition({ SCREEN_WIDTH / 2.f - introText.getGlobalBounds().size.x / 2.f, SCREEN_HEIGHT / 2.f - introText.getGlobalBounds().size.y / 2.f });

	Clock introClock;
	float elapsed = 0.f;
	while (elapsed < 6.f)
	{
		elapsed = introClock.getElapsedTime().asSeconds();

		if (elapsed < 3.5f) //time before fade out
		{
			introText.setFillColor(Color(255, 255, 255, (int)(255 * std::min(elapsed, 1.f))));
		}
		else if (elapsed < 4.5f)
		{
			introText.setFillColor(Color(255, 255, 255, (int)(255 * std::max(4.5f-elapsed, 0.f)))); //fade out
		}

		window.clear();
		drawTextShadered(window, introText, halo);
		window.display();
	}
	Flowey.reset();
	Starwalker.reset();
	Asgore.reset();

}

void initTitle()
{
	sndTitle.setLooping(true);
	sndTitle.play();
}

void Game::initialize()
{
	window = RenderWindow(VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "Five Nights at Asgore's (because Flower King does not sound as good, I think. It also made the title too long... but now it's even longer because of this explanation...)",
		State::Fullscreen);
	window.setFramerateLimit(144);
	sprDrink.setScale({ 0.1f, 0.1f });
	if (currentState  == GameState::Title) initTitle();
	sndBuzz.setVolume(30.f);
	run();
}

void Game::run()
{
	while (window.isOpen())
	{
		update();
		render();
	}
}


int GCount = 0;

GameState updateTitle(RenderWindow &window)
{
	const static float xPos = 70;
	const static float pos1 = 412.f;
	const static float pos2 = 470.f;
	const static float pos3 = 523.f;
	const static float pos4 = 578.f;


	static float lastPos = pos1;

	static rectPoint newGameButton({ 119.f, 409.f }, { 345.f, 440.f });
	static rectPoint continueButton({ 119.f, 460.f }, { 345.f, 507.f });
	static rectPoint sixthNightButton({ 119.f, 518.f }, { 345.f, 562.f });
	static rectPoint customNightButton({ 119.f, 572.f }, { 345.f, 611.f });
	static rectPoint creditsButton({ 0.f, 0.f }, { 72.f, 28.f });

	Vector2i mousePos = Mouse::getPosition();
	Vector2f mousePosF = { mousePos.x * 1.f, mousePos.y * 1.f };


	float posRequired =
		(mousePosF.y >= customNightButton.A.y) ? pos4 :
		(mousePosF.y >= sixthNightButton.A.y) ? pos3 :
		(mousePosF.y >= continueButton.A.y) ? pos2 :
		(mousePosF.y >= newGameButton.A.y) ? pos1 :
		pos1;


	sprSelect.setPosition({xPos, posRequired});
	if (posRequired != lastPos)
		sndSelect.play();
	lastPos = posRequired;

	if (!click) 	return GameState::Title;

	if (isInsideRect(creditsButton, mousePosF))
	{
		sndTitle.stop();
		return GameState::Credits;
	}


	if (isInsideRect(newGameButton, mousePosF))
	{
		sndTitle.stop();
		sndFriend.play();
		game.currentNight = &night1;
		startNight(window);
		return GameState::Office;
	}

	if (isInsideRect(continueButton, mousePosF))
	{
		sndTitle.stop();
		game.load();
		if (game.currentNight->num > 5) game.currentNight = &night5;
		startNight(window);
		return GameState::Office;
	}

	if (isInsideRect(sixthNightButton, mousePosF))
	{
		sndTitle.stop();
		game.currentNight = &night6;
		startNight(window);
		return GameState::Office;
	}

	if (isInsideRect(customNightButton, mousePosF))
	{
		sndTitle.stop();
		return GameState::CustomNight;
	}
	return GameState::Title;
}

extern bool G;
RectangleShape boopHitbox({ 50, 50 }); //boop ralsei :3

rectPoint bigDoor({ 600, 200 }, { 1035, 582 });
rectPoint smallDoor({ 80, 487 }, { 177, 670 });

GameState updateAndRenderWin()
{
	static Text text(font);
	static Clock clocky;
	static Vector2f pos = Vector2f({ SCREEN_WIDTH / 2.f - text.getGlobalBounds().size.x / 2.f, SCREEN_HEIGHT / 2.f - text.getGlobalBounds().size.y / 2.f });
	if (!clocky.isRunning()) clocky.start();

	float elapsed = clocky.getElapsedTime().asSeconds();

	if (elapsed > 10.f)
	{
		text.setFillColor(Color(255, 255, 255, 255)); //reset alpha
		clocky.reset();
		game.reset();
		if (game.currentNight == &night1) game.currentNight = &night2;
		else if (game.currentNight == &night2) game.currentNight = &night3;
		else if (game.currentNight == &night3) game.currentNight = &night4;
		else if (game.currentNight == &night4) game.currentNight = &night5;
		else if (game.currentNight == &night5) return GameState::Credits;
		else return GameState::Title;

		game.save(); //save after the night is set to new night

		startNight(game.getWindow());
		return GameState::Office;
	}

	if (elapsed < 5.f)
	{
		text.setPosition({ pos.x + std::sin(randRange(0, 255) * 1.f), pos.y + std::cos(randRange(0, 255) * 1.f) });
		text.setString("5:59 AM");
	}
	else if (elapsed < 7.f)
	{
		if (sndCheer.getStatus()!=Sound::Status::Playing) sndCheer.play();
		text.setPosition(pos);
		text.setString("6:00 AM");
	}
	else
	{
		text.setFillColor(Color(255, 255, 255, (int)(255 * std::max((10.f - elapsed), 0.f)))); //fade out
	}

	drawTextShadered(game.getWindow(), text, halo);

	return GameState::Win;

}

GameState updateOffice(Game &game)
{
	Flowey.update();
	Starwalker.update();
	Asgore.update();
	Knight.update();

	GCount += G;
	if (GCount > 666)
		std::exit(666);

	if (game.currentState != GameState::Office)
		return game.currentState;
	static float scrollSpeed = 1000.f;
	Vector2i mousePos = Mouse::getPosition();
	Vector2f mousePosF = { mousePos.x*1.f, mousePos.y*1.f };
	if (mousePos.x < 400)
	{
		Vector2f pos = sprOffice.getPosition();
		pos.x = std::min(pos.x + scrollSpeed*deltaTime, 0.f);
		sprOffice.setPosition(pos);
	}
	else if (mousePos.x > SCREEN_WIDTH - 400)
	{
		Vector2f pos = sprOffice.getPosition();
		pos.x = std::max(pos.x - scrollSpeed*deltaTime, SCREEN_WIDTH - 1600.f);
		sprOffice.setPosition(pos);
	}
	 
	Vector2f camOffset = sprOffice.getPosition(); // The current camera scroll thingy offset whatever uhhhhhh yeah i guess well this is the camera offset sooo that's it i guess so i hope u got the point like yes ofc this is the camera offset in case u didnt get the point of this comment yet. Anyway, this is the current camera scroll thingy offset whatever uhhhhhh yeah i guess well this is the camera offset sooo that's it i guess so i hope u got the point like yes ofc this is the camera offset 
	rectPoint cameraBounds({ 1115.f + camOffset.x, 383.f + camOffset.y }, { 1383.f + camOffset.x, 607.f + camOffset.y });

	rectPoint bigDoorTemp({ 600 + camOffset.x, 200 + camOffset.y }, { 1035 + camOffset.x, 582 + camOffset.y });
	rectPoint smallDoorTemp({ 80 + camOffset.x, 487 + camOffset.y }, { 177 + camOffset.x, 670 + camOffset.y });

	bigDoor = bigDoorTemp;
	smallDoor = smallDoorTemp;

	Vector2f smallDoorPos = { 85 + camOffset.x, 487 + camOffset.y };
	sprSmallDoor.setPosition(smallDoorPos);
	sprSmallDoorF.setPosition(smallDoorPos);

	Vector2f bigDoorPos = { 600 + camOffset.x, 230 + camOffset.y };
	sprBigDoor.setPosition(bigDoorPos);
	sprBigDoorF.setPosition(bigDoorPos);
	sprBigDoorS.setPosition(bigDoorPos);


	if (click && isInsideRect(cameraBounds, mousePosF))
	{
		G = false;
		sndCamOpen.play();
		return GameState::Camera;
	}

	boopHitbox.setPosition({ sprOffice.getPosition().x + 1469.f, 558.f });
	if (click && boopHitbox.getGlobalBounds().contains(mousePosF) && sndBoop.getStatus()!=Sound::Status::Playing)
		sndBoop.play();
	return GameState::Office;
}

Clock deltaClock;
float deltaTime = 1;

void Game::update()
{
	deltaTime = deltaClock.restart().asSeconds();
	click = false;
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
		if (event->is<Event::MouseButtonPressed>())
		{
			click = true;
		}
	}

	switch (currentState)
	{
	case GameState::Title:
		currentState = updateTitle(window);
		break;
	case GameState::Office:
		currentState = updateOffice(*this);
		break;
	case GameState::Camera:
		currentState = updateCamera();
		break;
	case GameState::Jumpscare:
		jumpscare();
		break;
	case GameState::Death:
		handleCalls();
		deathScreen();
		break;
	break;
	}
	//update hall, im lazy to put it where im supposed to because i want this to always be updated
	static Clock panClock;
	static bool movingLeft = true;
	static float xMax = 440.f;
	static float x = 0.f;

	float panSpeed = 120.f;

	if (panClock.getElapsedTime().asSeconds() > 5.f)
	{
		movingLeft = !movingLeft;
		panClock.restart();
	}

	if (movingLeft)
		x -= panSpeed * deltaTime;
	else
		x += panSpeed * deltaTime;

	x = std::clamp(x, -xMax, 100.f);
	sprHall.setPosition({ x, 0.f });

}

void renderTitle(RenderWindow &window)
{
	static IntRect full({ 0, 0}, {SCREEN_WIDTH, SCREEN_HEIGHT});
	sprTitle.setTextureRect(full);
	sprTitle.setPosition({ 0 , 0 });
	window.draw(sprTitle, &bloom);
	static IntRect rightHalf({ SCREEN_WIDTH / 2-30, 0 }, { SCREEN_WIDTH / 2 +30, SCREEN_HEIGHT});
	sprTitle.setTextureRect(rightHalf);
	sprTitle.setPosition({ SCREEN_WIDTH / 2 -30 , 0 });
	window.draw(sprTitle);
	window.draw(sprSelect, &bloom);
}


void renderOffice(RenderWindow &window)
{
	if (G)
	{
		{ { { { { { {} } } } } }
		static Texture tMysteryMan("res/img/mysteryman.png");
		sprOffice.setTexture(tMysteryMan);
		} {} {}
	}
	else if (&sprOffice.getTexture() != &t_sprOffice) sprOffice.setTexture(t_sprOffice);


	window.draw(sprOffice);
	if (!Mouse::isButtonPressed(Mouse::Button::Left))
	{
		Flowey.isFlashed = false;
		Starwalker.isFlashed = false;
		sndBuzz.stop();
		return;
	}
	Vector2i mousePos = Mouse::getPosition(window);
	Vector2f mousePosF = { mousePos.x * 1.f, mousePos.y * 1.f };
	if (isInsideRect(smallDoor, mousePosF))
	{
		if (sndBuzz.getStatus() != Sound::Status::Playing) sndBuzz.play();
		if (floweySmallDoor)
		{
			window.draw(sprSmallDoorF);
			Flowey.isFlashed = true;
		}
		else
		{
			window.draw(sprSmallDoor);
		}
	}
	else if (isInsideRect(bigDoor, mousePosF))
	{
		if (sndBuzz.getStatus() != Sound::Status::Playing) sndBuzz.play();
		if (floweyBigDoor)
		{
			window.draw(sprBigDoorF);
			Flowey.isFlashed = true;
			if (sndFnaf2Hall.getStatus() != Sound::Status::Playing) sndFnaf2Hall.play();

		}
		else if (starwalkerBigDoor)
		{
			window.draw(sprBigDoorS);
			Starwalker.isFlashed = true;
			if (sndFnaf2Hall.getStatus() != Sound::Status::Playing) sndFnaf2Hall.play();

		}
		else
		{
			window.draw(sprBigDoor);
		}
	}
	else
	{
		sndBuzz.stop();
		Flowey.isFlashed = false;
		Starwalker.isFlashed = false;
	}

}

void Game::render()
{
	window.clear();

	switch (currentState)
	{
	case GameState::Title:
		renderTitle(window);
		break;
	case GameState::Office:
		renderOffice(window);
		handleCalls();
		break;
	case GameState::Camera:
		renderCamera(window);
		handleCalls();
		break;
	case GameState::Win:
		currentState = updateAndRenderWin(); //cannot be put in update cuz this draws and stuff, so it would get cleared before draw cuz uhhh the order is update() and then render()
		break;
	case GameState::CustomNight:
		customNight(window);
		break;
	case GameState::Minigame:
		minigame();
		break;
	case GameState::Credits:
		handleCredits();
		break;
	case GameState::Warning:
		warning();
		break;
	}

	updateTimer(window);
	waitForQuit(); //requires display stuff sooo in render

	window.display();
}


void Game::reset()
{
	jumpscareCulprit = 'F';
	Flowey.reset();
	Starwalker.reset();
	Asgore.reset();
}