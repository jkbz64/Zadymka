#include <Physics/Util.hpp>

namespace
{
    constexpr float worldScale = 100.f;
}

b2::Vec2 vecToBoxVec(const glm::vec2& vec)
{
    return b2::Vec2(vec.x / worldScale, -vec.y / worldScale);
}

glm::vec2 boxToVec(const b2::Vec2& vec)
{
    return glm::vec2(vec.x, -vec.y) * worldScale;
}

float floatToBoxFloat(float val)
{
    return val / worldScale;
}

float boxToFloat(float val)
{
    return val * worldScale;
}
