#include "game.hpp"
#include "globals.hpp"
#include "resources.hpp"
#include "camera.hpp"
#include "animatronics.hpp"
#include "timer.hpp"
//#include "jumpscare.hpp"

using namespace sf;

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
	initTitle();
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

void initializeOffice()
{
	sprOffice.setPosition({-170.f, 0.f});
	initTimer();
}

int GCount = 0;

GameState updateTitle(RenderWindow &window)
{
	const static float xPos = 70;
	const static float pos1 = 412.f;
	const static float pos2 =  470.f;

	static float lastPos = pos1;

	float posRequired = Mouse::getPosition(window).y > 470 ? pos2 : pos1;
	sprSelect.setPosition({xPos, posRequired});
	if (posRequired != lastPos)
		sndSelect.play();
	lastPos = posRequired;

	if (click)
	{
		sndTitle.stop();
		initializeOffice();
		return GameState::Office;
	}
	return GameState::Title;

}

extern bool G;
RectangleShape boopHitbox({ 50, 50 }); //boop ralsei :3

rectPoint bigDoor({ 600, 200 }, { 1035, 582 });
rectPoint smallDoor({ 80, 487 }, { 177, 670 });

GameState updateOffice(Game &game)
{
	Flowey.update();
	Starwalker.update();
	Asgore.update();

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
		deathScreen();
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
	window.draw(sprTitle);
	window.draw(sprSelect);
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
		break;
	case GameState::Camera:
		renderCamera(window);
		break;
	}

	updateTimer(window);

	window.display();
}


void Game::reset()
{
	currentState = GameState::Title;
	jumpscareCulprit = 'F';
	Flowey.reset();
	initTitle();
}