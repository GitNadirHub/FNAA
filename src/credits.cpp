#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "game.hpp"
#include "globals.hpp"
#include "resources.hpp"
#include <sstream>
using namespace std;

vector<string> creditBlocks = {
    "",
    "A game by\nNadir",
    "Deltarune and Undertale\nby Toby Fox",
    "Five Nights at Freddy's\nby Scott Cawthon",
    "Asgore runs over Dess (with lyrics)\nby Bub8les, KennyTheLyr1c1st",
    "The Original Starwalker\nOriginal VA: yesto690",
    "Bugs you may encounter:\nChara",
    "Singing this song - ???",
    "Cast:\nTogore Dreemurr - Togore Dreemurr\nPapyrus - Brian\nAsgore Deltarune - Asgore Undertale\nStarwalker - Starwalker",
    "PLAYTESTERS:\ndadanti360\nInfinit Ninja\nMist\nMrStoica\n(Thanks a lot guys :D)",
    "Thanks for playing! <3"
};


int currentBlock = 0;
float timer = 0.f;
float fadeDuration = 3.0f;
float displayDuration = 2.0f;

enum State { FadeIn, Show, FadeOut };
State state = FadeIn;

sf::Text text(font);

std::vector<sf::Text> currentLines;

void setCreditBlock(int index)
{
    currentLines.clear();
    istringstream iss(creditBlocks[index]);
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
    float y = (SCREEN_HEIGHT / 2.f) - (totalHeight / 2.f);
    for (auto& t : temp)
    {
        sf::FloatRect b = t.getLocalBounds();
        t.setPosition({ SCREEN_WIDTH / 2.f, y + b.size.y / 2.f});
        y += b.size.y + 30.f;
        currentLines.push_back(t);
    }
}

void Game::handleCredits()
{
    timer += deltaTime;

    float alpha = 255.f;
    if (state == FadeIn)
    {
        alpha = min(255.f, (timer / fadeDuration) * 255.f);
        if (timer >= fadeDuration) { state = Show; timer = 0.f; }
    }
    else if (state == Show)
    {
        if (timer >= displayDuration) { state = FadeOut; timer = 0.f; }
    }
    else if (state == FadeOut)
    {
        alpha = max(0.f, 255.f - (timer / fadeDuration) * 255.f);
        if (timer >= fadeDuration)
        {
            currentBlock++;
            if (currentBlock >= creditBlocks.size())
            {
                currentState = GameState::Title;
                initTitle();
            }
            else
            {
                setCreditBlock(currentBlock);
                state = FadeIn;
            }
            timer = 0.f;
        }
    }

    for (auto& t : currentLines)
    {
        t.setFillColor(sf::Color(255, 255, 255, alpha));
        window.draw(t);
    }
}
