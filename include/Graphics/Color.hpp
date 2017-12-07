#ifndef COLOR_HPP
#define COLOR_HPP
#include <glm/fwd.hpp>

class Color
{
public:
    Color();
    Color(int, int, int, int);
    Color(const Color&) = default;
    Color(Color&&) = default;
    Color& operator=(const Color&) = default;
    Color& operator=(Color&&) = default;
    ~Color() = default;

    glm::vec4 normalized() const;
    int r() const;
    int g() const;
    int b() const;
    int a() const;

    //Static basic colors
    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Transparent;
private:
    friend class Graphics;
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
