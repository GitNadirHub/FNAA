#pragma once
#include <SFML/Graphics.hpp>

enum class GameState {Title, Office, Camera};

class Game {
public:
	void initialize(), run();
private:
	sf::RenderWindow window;
	void update(), render();
	GameState currentState = GameState::Title;
};