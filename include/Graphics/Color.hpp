#ifndef COLOR_HPP
#define COLOR_HPP
#include <glm/vec4.hpp>
#include <array>

class Color
{
public:
    //Static basic colors
    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Transparent;

    Color();
    Color(int, int, int, int);
    Color(const Color&) = default;
    Color(Color&&) = default;
    Color& operator=(const Color&) = default;
    Color& operator=(Color&&) = default;
    ~Color() = default;

    std::array<float, 4> normalized();
    int r() const;
    int g() const;
    int b() const;
    int a() const;
private:
    int m_r;
    int m_g;
    int m_b;
    int m_a;
};

inline int Color::r() const
{
    return m_r;
}

inline int Color::g() const
{
    return m_g;
}

inline int Color::b() const
{
    return m_b;
}

inline int Color::a() const
{
    return m_a;
}

#endif
