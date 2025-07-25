#include "globals.hpp"

bool isInsideRect(const rectPoint& rect, const sf::Vector2f& P)
{
    float left = std::min(rect.A.x, rect.B.x);
    float right = std::max(rect.A.x, rect.B.x);
    float top = std::min(rect.A.y, rect.B.y);
    float bottom = std::max(rect.A.y, rect.B.y);

    return (P.x >= left && P.x <= right && P.y >= top && P.y <= bottom);
}
