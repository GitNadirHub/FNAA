#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "game.hpp"
#include "timer.hpp"
#include <string>
#include "animatronics.hpp"

Game game;

int main()
{
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
	window.draw(hourText);

	std::string drunkString = "Drinks absored by Asgore: " + std::to_string(Asgore.consumed) + "/7";

	drunkText.setString(drunkString);

	window.draw(drunkText);


}

