#ifndef UTIL_HPP
#define UTIL_HPP
#include <glm/vec2.hpp>
#include <Box2D/Common/Math.hpp>

b2::Vec2 vecToBoxVec(const glm::vec2& vec);
glm::vec2 boxToVec(const b2::Vec2& vec);
float floatToBoxFloat(float val);
float boxToFloat(float val);

#endif
