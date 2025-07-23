#include "game.hpp"
#include "globals.hpp"
#include "resources.hpp"
using namespace sf;

void Game::initialize()
{
	window = RenderWindow(VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "Five Nights at Asgore's (because Flower King does not sound as good, I think. It also made the title too long... but now it's even longer because of this explanation...)",
		State::Fullscreen);
	window.setFramerateLimit(144);
	sndTitle.setLooping(true);
	sndTitle.play();
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
}


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

	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		sndTitle.stop();
		initializeOffice();
		return GameState::Office;
	}
	return GameState::Title;

}

RectangleShape boopHitbox({ 50, 50 }); //boop ralsei :3

GameState updateOffice()
{

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

	boopHitbox.setPosition({ sprOffice.getPosition().x + 1469.f, 558.f });
	if (Mouse::isButtonPressed(Mouse::Button::Left) && boopHitbox.getGlobalBounds().contains(mousePosF) && sndBoop.getStatus()!=Sound::Status::Playing)
		sndBoop.play();
	return GameState::Office;
}

Clock deltaClock;
float deltaTime = 1;

void Game::update()
{
	deltaTime = deltaClock.restart().asSeconds();

	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
	}

	switch (currentState)
	{
	case GameState::Title:
		currentState = updateTitle(window);
		break;
	case GameState::Office:
		currentState = updateOffice();
		break;
	}
}

void renderTitle(RenderWindow &window)
{
	window.draw(sprTitle);
	window.draw(sprSelect);
}

void renderOffice(RenderWindow &window)
{
	window.draw(sprOffice);
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
	}
	window.display();
}
