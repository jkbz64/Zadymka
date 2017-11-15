#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <Graphics/Drawable.hpp>
#include <Graphics/Texture.hpp>

class Sprite : public Drawable<Sprite>
{
public:
    static void registerClass();
    Sprite();
    Sprite(const Sprite&);
    Sprite& operator=(const Sprite&);
    Sprite(Sprite&&);
    Sprite& operator=(Sprite&&);
    virtual ~Sprite() = default;
    void setTexture(const Texture&);
    const Texture& getTexture();
    void setPosition(const glm::vec2&);
    const glm::vec2& getPosition();
    void setSize(const glm::vec2&);
    const glm::vec2& getSize();
protected:
    virtual void draw(Window&) override;
    Texture m_texture;
};

#endif
