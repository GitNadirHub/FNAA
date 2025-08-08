#include "quitting.hpp"
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "resources.hpp"
using namespace sf;

Clock quitClock;

bool handleQuitting()
{
	if (!Keyboard::isKeyPressed(Keyboard::Key::Escape)) return false;

	float elapsed = quitClock.getElapsedTime().asSeconds();

	auto& window = game.getWindow();

	static Text txt(font);

	int dotCount = 0;
	if (elapsed < 1.f) dotCount = 1;
	else if (elapsed < 2.f) dotCount = 2;
	else if (elapsed < 3.f) dotCount = 3;
	else dotCount = 3;

	std::string dots(dotCount, '.');

	txt.setString("Quitting" + dots);

	window.draw(txt);

	if (elapsed > 3.1f)
	{
		game.close();
	}

	return true;
}

void waitForQuit()
{
	static bool wasPressed = false;
	if (wasPressed)
	{
		wasPressed = handleQuitting();
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		quitClock.restart();
		handleQuitting();
		wasPressed = true;
		return;
	}
	wasPressed = false;
}

void Game::close()
{
	save();
	//for now
	window.close();
}