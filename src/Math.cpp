#include <Math.hpp>
#include <Lua.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

void Math::registerModule()
{
    Lua::getState().new_usertype<glm::vec2>("Vec2f",
                                            sol::constructors<glm::vec2(), glm::vec2(float, float), glm::vec2(glm::vec2), glm::vec2(const glm::vec2&), glm::vec2(const glm::uvec2&)>(),
                                            "x", &glm::vec2::x,
                                            "y", &glm::vec2::y,
                                            sol::meta_function::addition, [](const glm::vec2& a, const glm::vec2& b)
                                            {
                                                return a + b;
                                            },
                                            sol::meta_function::subtraction, [](const glm::vec2& a, const glm::vec2& b)
                                            {
                                                return a - b;
                                            },
                                            sol::meta_function::multiplication, [](const glm::vec2& a, float b)
                                            {
                                                return a * b;
                                            },
                                            sol::meta_function::division, [](const glm::vec2& a, float b)
                                            {
                                                return a / b;
                                            },
                                            sol::meta_function::equal_to, [](const glm::vec2& a, const glm::vec2& b)
                                            {
                                                return a == b;
                                            }
    );

    Lua::getState().new_usertype<glm::uvec2>("Vec2u",
                                            sol::constructors<glm::uvec2(), glm::uvec2(unsigned int, unsigned int), glm::uvec2(glm::uvec2), glm::uvec2(const glm::uvec2&), glm::uvec2(const glm::vec2&)>(),
                                            "x", &glm::uvec2::x,
                                            "y", &glm::uvec2::y,
                                            sol::meta_function::addition, [](const glm::uvec2& a, const glm::uvec2& b)
                                            {
                                                return a + b;
                                            },
                                            sol::meta_function::subtraction, [](const glm::uvec2& a, const glm::uvec2& b)
                                            {
                                                return a - b;
                                            },
                                            sol::meta_function::multiplication, [](const glm::uvec2& a, float b)
                                            {
                                                return a * static_cast<unsigned int>(b);
                                            },
                                            sol::meta_function::division, [](const glm::uvec2& a, float b)
                                            {
                                                return a / static_cast<unsigned int>(b);
                                            },
                                            sol::meta_function::equal_to, [](const glm::uvec2& a, const glm::uvec2& b)
                                            {
                                                return a == b;
                                            }
    );

    Lua::getState().new_usertype<glm::ivec2>("Vec2i",
                                            sol::constructors<glm::ivec2(), glm::ivec2(int, int), glm::ivec2(glm::ivec2), glm::ivec2(const glm::ivec2&), glm::ivec2(const glm::vec2&)>(),
                                            "x", &glm::ivec2::x,
                                            "y", &glm::ivec2::y,
                                            sol::meta_function::addition, [](const glm::ivec2& a, const glm::ivec2& b)
                                            {
                                                return a + b;
                                            },
                                            sol::meta_function::subtraction, [](const glm::ivec2& a, const glm::ivec2& b)
                                            {
                                                return a - b;
                                            },
                                            sol::meta_function::multiplication, [](const glm::ivec2& a, float b)
                                            {
                                                return a * static_cast<int>(b);
                                            },
                                            sol::meta_function::division, [](const glm::ivec2& a, float b)
                                            {
                                                return a / static_cast<int>(b);
                                            },
                                            sol::meta_function::equal_to, [](const glm::ivec2& a, const glm::ivec2& b)
                                            {
                                                return a == b;
                                            }
    );
}
