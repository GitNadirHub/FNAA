#include "game.hpp" 
#include "resources.hpp"
#include "globals.hpp"
#include <sstream>
#include <vector>
using namespace sf;


static std::vector<sf::Text> currentLines;

void setStringBlock(std::string str)
{
    using namespace std;
    currentLines.clear();
    istringstream iss(str);
    string line;
    float totalHeight = 0.f;
    vector<sf::Text> temp;
    while (getline(iss, line))
    {
        sf::Text t(font);
        t.setString(line);
        sf::FloatRect b = t.getLocalBounds();
        t.setOrigin({ b.size.x / 2.f, b.size.y / 2.f });
        temp.push_back(t);
        totalHeight += b.size.y;
    }
    float y = (SCREEN_HEIGHT / 3.f) - (totalHeight / 2.f);
    for (auto& t : temp)
    {
        sf::FloatRect b = t.getLocalBounds();
        t.setPosition({ SCREEN_WIDTH / 3.f, y + b.size.y / 2.f });
        y += b.size.y + 30.f;
        currentLines.push_back(t);
    }
}

void Game::warning()
{
	static Clock warnClock;
	float elapsed = warnClock.getElapsedTime().asSeconds();

    /// NIKO STUFF :p
	if (elapsed < 2.f)
	{
		sprNiko.setPosition({ 1280.f, 373.f });
		window.draw(sprNiko);
		return;
	}

    if (elapsed > 12.5f || Keyboard::isKeyPressed(Keyboard::Key::F9))
    {
        currentState = GameState::Title;
        initTitle();
    }

	static const float targetPos = 850.f;
	float pos = sprNiko.getPosition().x;
	if (pos - targetPos < 0.5) pos = targetPos;
	else pos += 2 * (targetPos - pos) * deltaTime;
	sprNiko.setPosition({ pos, 373.f });
	window.draw(sprNiko);


    /// TEXT STUFF >:3
    
    static std::string finalText = "Warning!\nThe following game\ncontains loud noises,\nflashing lights\nand jumpscares.\nThis game\nmight be spoopy...\n \nHave fun! :p\n";

    static const float delay = 0.060f; // 60 ms per char
    float typingTime = elapsed - 2; // 2 is the start of all this so yeh

    int index = (int) (typingTime/delay);

    std::string text = finalText.substr(0, std::min((int)finalText.size(), index));

    setStringBlock(text);

    for (auto& t : currentLines)
    {
        window.draw(t);
    }

}