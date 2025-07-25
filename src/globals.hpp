#pragma once
#include <SFML/Graphics.hpp>

const unsigned int SCREEN_WIDTH = 1280u;
const unsigned int SCREEN_HEIGHT = 720u;

extern sf::Clock deltaClock;
extern float deltaTime;

struct rectPoint
{
    sf::Vector2f A; // Top-left corner
    sf::Vector2f B; // Bottom-left corner

    rectPoint(const sf::Vector2f& a, const sf::Vector2f& b): A(a), B(b) {}
};

extern bool isInsideRect(const rectPoint& rect, const sf::Vector2f& P);