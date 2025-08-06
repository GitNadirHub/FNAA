#pragma once
#include <SFML/Graphics.hpp>

enum class GameState {Title, Office, Camera, Jumpscare, Death, Win};

struct Night {
	int AILEVELS[4];
	void initNight();
	Night(int a, int b, int c, int d)
	{
		AILEVELS[0] = a;
		AILEVELS[1] = b;
		AILEVELS[2] = c;
		AILEVELS[3] = d;
	}
};

extern Night night1, 
	  night2,
	  night3,
	  night4,
	  night5,
	  night6;


class Game {
public:
	Night* currentNight = &night1;
	void initialize(), run();
	void close() { window.close(); }
	char jumpscareCulprit = 'F';
	GameState currentState = GameState::Title;

private:
	sf::RenderWindow window;
	void update(), render();
	void jumpscare(), deathScreen();
	void reset();
};

void initTitle();

extern Game game;