#pragma once
#include <SFML/Graphics.hpp>

enum class GameState {Title, Office, Camera, Jumpscare, Death, Win};

class Game {
public:
	void initialize(), run();
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