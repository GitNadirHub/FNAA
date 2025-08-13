#include "game.hpp"
#include "resources.hpp"
#include "globals.hpp"
using namespace sf;

#define isPressed(x) Keyboard::isKeyPressed(Keyboard::Key::x)

void first(RenderWindow)
{
//	window.draw()
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


	float xVelocity = (isPressed(D)||isPressed(Right)) - (isPressed(A) || isPressed(Left));
	float yVelocity = (isPressed(S)||isPressed(Down)) - (isPressed(W) || isPressed(Up));
	static const float speed = 140.f;
	xVelocity *= speed * deltaTime;
	yVelocity *= speed * deltaTime;

	Vector2f velocity = { xVelocity, yVelocity };

	sprSoul.setPosition(sprSoul.getPosition() + velocity);

	window.draw(sprKrisRoom);
	window.draw(sprSoul);
}

void Game::minigame()
{
	second(window);
}