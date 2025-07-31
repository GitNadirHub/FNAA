#include "globals.hpp"

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