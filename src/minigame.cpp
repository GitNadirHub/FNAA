#include "game.hpp"
#include "resources.hpp"
#include "globals.hpp"
using namespace sf;

#define isPressed(x) Keyboard::isKeyPressed(Keyboard::Key::x)

void first(RenderWindow)
{
//	window.draw()
}

void move()
{
	float xVelocity = (isPressed(D) || isPressed(Right)) - (isPressed(A) || isPressed(Left));
	float yVelocity = (isPressed(S) || isPressed(Down)) - (isPressed(W) || isPressed(Up));
	static const float speed = 140.f;
	xVelocity *= speed * deltaTime;
	yVelocity *= speed * deltaTime;

	Vector2f velocity = { xVelocity, yVelocity };

	sprSoul.setPosition(sprSoul.getPosition() + velocity);
}

void second(RenderWindow& window)
{

	static const bool initialize = []() {
		FloatRect bounds = sprKrisRoom.getLocalBounds();
		sprKrisRoom.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
		sprKrisRoom.setPosition({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
		sprKrisRoom.setScale({ 2.f, 2.f });

		return true;
		}();


	move();

	window.draw(sprKrisRoom);
	window.draw(sprSoul);
}

void newspaper(RenderWindow& window)
{
	static Texture t_sprNP("res/img/newspaper.png");
	static Sprite sprNP(t_sprNP);

	auto mousePosI = Mouse::getPosition();
	Vector2f mousePos = { mousePosI.x * 1.f, mousePosI.y * 1.f };

	static const float imageHeight = sprNP.getTexture().getSize().y * 0.5; //*scale
	static const float yMax = imageHeight - SCREEN_HEIGHT;

	float pos = (sprSoul.getPosition().y / (SCREEN_HEIGHT - sprSoul.getTexture().getSize().y))* yMax;
	pos = std::clamp(pos, 0.f, yMax);
	sprNP.setScale({ 0.5, 0.5 });

	sprNP.setPosition({ 20.f, -pos });

	move();

	window.draw(sprNP);
	window.draw(sprSoul);
}

void Game::minigame()
{
	static bool yes = 0;
	if (sprSoul.getPosition().y > SCREEN_HEIGHT)
	{
		yes = true;
		sprSoul.setPosition({ 680, 300 });
	}
	else if (yes)
		newspaper(window);
	else
		second(window);
}


