#include "game.hpp"

using namespace sf;

Clock fadeClock;

void Game::deathScreen()
{
    static Texture tDeath("res/img/gameover.png");
    static Texture tRan("res/img/ranover.png");
    static Sprite sprDeath(tDeath);

    if (jumpscareCulprit == 'A') sprDeath.setTexture(tRan);
    else sprDeath.setTexture(tDeath);

    fadeClock.restart();

    while (currentState == GameState::Death)
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
            }
        }

        float t = fadeClock.getElapsedTime().asSeconds();

        if (t < 1.f)
        {
            sprDeath.setColor(Color(255, 255, 255, 0));
        }
        else if (t < 2.f)
        {
            float alpha = (t - 1.f) * 255;
            sprDeath.setColor(Color(255, 255, 255, (int)(alpha)));
        }
        else if (t < 6.f)
        {
            sprDeath.setColor(Color(255, 255, 255, 255));
        }
        else if (t < 8.f)
        {
            float alpha = (1.f - (t - 6.f) / 2.f) * 255;
            sprDeath.setColor(Color(255, 255, 255, (int)(alpha)));
        }
        else if (t < 9.f)
        {
            sprDeath.setColor(Color(255, 255, 255, 0));
        }
        else
        {
            fadeClock.restart();
            reset();
        }

        window.clear();
        window.draw(sprDeath);
        window.display();
    }
}
