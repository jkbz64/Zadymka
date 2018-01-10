#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <Graphics/Rectangle.hpp>
#include <Graphics/Texture.hpp>

class Sprite : public Rectangle
{
public:
    Sprite();
    Sprite(const Sprite&);
    Sprite& operator=(const Sprite&);
    Sprite(Sprite&&);
    Sprite& operator=(Sprite&&);
    virtual ~Sprite() = default;
    
    const Texture& texture() const;
    const glm::vec2& position() const;
    const glm::vec2& size() const;
    
    void setTexture(const Texture&);
    void setPosition(const glm::vec2&);
    void setSize(const glm::vec2&);
protected:
    friend class Graphics;
    void draw(Renderer*) override;
    Texture m_texture;
};

#endif
