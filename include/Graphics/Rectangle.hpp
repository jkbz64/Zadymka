#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <Graphics/Drawable.hpp>
#include <Graphics/Color.hpp>

class Rectangle : public Drawable, public Transformable
{
public:
    static void registerClass(sol::table);
    Rectangle();
    Rectangle(unsigned, unsigned);
    Rectangle(const Rectangle&);
    Rectangle& operator=(const Rectangle&);
    Rectangle(Rectangle&&);
    Rectangle& operator=(Rectangle&&);
    ~Rectangle() = default;
    void setPosition(const glm::vec2&);
    const glm::vec2& getPosition();
    void setSize(const glm::vec2&);
    const glm::vec2& getSize();
    const Color& getColor();
    void setColor(const Color&);
protected:
    virtual void draw(const Shader&) override;
    virtual GLuint update() override;
    virtual Shader& getDefaultShader() override;
};

#endif
