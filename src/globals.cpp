#include "globals.hpp"
#include <iostream>
int FUN = 17;

bool isInsideRect(const rectPoint& rect, const sf::Vector2f& P)
{
    float left = std::min(rect.A.x, rect.B.x);
    float right = std::max(rect.A.x, rect.B.x);
    float top = std::min(rect.A.y, rect.B.y);
    float bottom = std::max(rect.A.y, rect.B.y);

    return (P.x >= left && P.x <= right && P.y >= top && P.y <= bottom);
}

int randRange(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

bool floweySmallDoor = false, floweyBigDoor = false;
bool starwalkerBigDoor = false;
bool click = false;

using namespace sf;

void drawTextShadered(sf::RenderWindow& window, sf::Text &text, sf::Shader& shader)
{
    FloatRect bounds = text.getLocalBounds();
    Vector2f textOgPos = text.getPosition(); //render textures use a different coordinate system
    text.setPosition({ 0.f, 0.f });
    Vector2u size = {(unsigned) bounds.size.x, (unsigned)bounds.size.y + 50 };
    RenderTexture rt(size);
    rt.clear(Color::Transparent);
    rt.draw(text); //draw the text to the render texture at 0, 0
    rt.display();
    Sprite sprite(rt.getTexture());
    text.setPosition(textOgPos); //set it back to the original pos
    sprite.setPosition(text.getPosition());
    window.draw(sprite, &shader);
}