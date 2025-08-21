#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "game.hpp"
#include "timer.hpp"
#include <string>
#include "animatronics.hpp"


#ifdef _WIN32
#include <windows.h>

int main();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	return main();
}
#endif



Game game;

int main()
{
	vignette.loadFromFile("res/shaders/vignette.frag", sf::Shader::Type::Fragment);
	vignetteStrong.loadFromFile("res/shaders/vignetteStrong.frag", sf::Shader::Type::Fragment);
	bloom.loadFromFile("res/shaders/bloom.frag", sf::Shader::Type::Fragment);
	halo.loadFromFile("res/shaders/halo.frag", sf::Shader::Type::Fragment);
    game.initialize();
}

int hour = 0;
sf::Clock hourTimer;
sf::Text hourText(font);

sf::Text drunkText(font);

void initTimer()
{
	hourTimer.restart();
	hourText.setPosition({1100.f, 10.f});
	hourText.setCharacterSize(30);
	hourText.setFillColor(sf::Color::White);
	hourText.setString("12 AM");

	drunkText.setPosition({ 970.f, 50.f });
	drunkText.setCharacterSize(10);

	hour = 0;
}

void updateTimer(sf::RenderWindow &window)
{
	if (game.currentState != GameState::Office && game.currentState != GameState::Camera)
		return;
	int elapsed = hourTimer.getElapsedTime().asSeconds();
	if (elapsed >= 70) //In Romania, every 70 seconds, an hour passes.
	{
		hourTimer.restart();
		hour++;
		std::string s = "";
		s = std::to_string(hour) + " AM";
		hourText.setString(s);
	}
	if (hour >= 6)
	{
		game.currentState = GameState::Win;
	}
	drawTextShadered(window, hourText, halo);

	std::string drunkString = "Drinks absorbed by Asgore: " + std::to_string(Asgore.consumed) + "/7";

	drunkText.setString(drunkString);

	drawTextShadered(window, drunkText, halo);

}