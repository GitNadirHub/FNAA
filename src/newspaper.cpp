#include "game.hpp"
#include "globals.hpp"

using namespace sf;

void newspaper(RenderWindow& window)
{
	static Texture t_sprNP("res/img/newspaper.png");
	static Sprite sprNP(t_sprNP);

	auto mousePosI = Mouse::getPosition();
	Vector2f mousePos = { mousePosI.x * 1.f, mousePosI.y * 1.f };

	static const float imageHeight = 3505.f;
	static const float yMax = imageHeight - SCREEN_HEIGHT;
	
	float pos = yMax * (mousePos.y/SCREEN_HEIGHT);

	sprNP.setPosition({20.f, pos});

	window.draw(sprNP);
}