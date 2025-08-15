#pragma once
#include <SFML/Graphics.hpp>

enum class GameState {Title, Office, Camera, Jumpscare, Death, Win, CustomNight, Minigame, Credits};

extern sf::Shader vignette;
extern sf::Shader vignetteStrong;
extern sf::Shader bloom;
extern sf::Shader halo;

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

	bool callPlayed = false;

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
	//GameState currentState = GameState::Credits;
	//GameState currentState = GameState::Minigame;
	//GameState currentState = GameState::CustomNight;
	void reset();
	void save();
	void load();
	sf::RenderWindow& getWindow() { return window; }
private:
	sf::RenderWindow window;
	void update(), render();
	void jumpscare(), deathScreen();
	void minigame();
	void handleCalls();
	void handleCredits();
};

void initTitle();

extern Game game;


void customNight(sf::RenderWindow &window);
void startNight(sf::RenderWindow& window);