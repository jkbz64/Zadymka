#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <Graphics/Rectangle.hpp>
#include <Graphics/Texture.hpp>

class Sprite : public Rectangle
{
public:
    static void registerClass(sol::table);
    Sprite();
    Sprite(const Sprite&);
    Sprite& operator=(const Sprite&);
    Sprite(Sprite&&);
    Sprite& operator=(Sprite&&);
    virtual ~Sprite() = default;
    void setTexture(const Texture&);
    const Texture& getTexture() const;
    void setPosition(const glm::vec2&);
    const glm::vec2& getPosition();
    void setSize(const glm::vec2&);
    const glm::vec2& getSize();
protected:
    Texture m_texture;
    Color m_color;
};

#endif
