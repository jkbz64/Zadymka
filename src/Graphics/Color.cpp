#include <Graphics/Color.hpp>
#include <glm/vec4.hpp>

namespace
{
    template <typename T>
    constexpr float normalize(T value)
    {
      return value < 0.f ? 0.f : static_cast<float>(value) / 255.f;
    }
}

Color::Color() :
    Color(0, 0, 0, 255)
{

}

Color::Color(int cr, int cg, int cb, int ca) :
    m_r(cr),
    m_g(cg),
    m_b(cb),
    m_a(ca)
{

}

glm::vec4 Color::normalized() const
{
    return glm::vec4(normalize(r()), normalize(g()), normalize(b()), normalize(a()));
}

//Define basic colors
const Color Color::Black(0, 0, 0, 255);
const Color Color::White(255, 255, 255, 255);
const Color Color::Red(255, 0, 0, 255);
const Color Color::Green(0, 255, 0, 255);
const Color Color::Blue(0, 0, 255, 255);
const Color Color::Transparent(0, 0, 0, 255);
