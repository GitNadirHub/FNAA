#pragma once
#include <SFML/Graphics.hpp>

enum class GameState {Title, Office, Camera, Jumpscare, Death, Win};

struct Night {
	int AILEVELS[4];
	void initNight();
	Night(int a, int b, int c, int d, int num)
	{
		AILEVELS[0] = a;
		AILEVELS[1] = b;
		AILEVELS[2] = c;
		AILEVELS[3] = d;
		this->num = num;
	}
	int num = 0; //for display and cleaner logic
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
	void close();
	char jumpscareCulprit = 'F';
	GameState currentState = GameState::Title;
	void reset();
	void save();
	void load();
	sf::RenderWindow& getWindow() { return window; }

private:
	sf::RenderWindow window;
	void update(), render();
	void jumpscare(), deathScreen();
};

void initTitle();

extern Game game;