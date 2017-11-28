#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include <Graphics/Shader.hpp>
#include <Graphics/Transformable.hpp>
#include <Graphics/Color.hpp>

class Window;

class Drawable
{
public:
    Drawable() = default;
    virtual ~Drawable() = default;
protected:
    friend class RenderTarget;
    virtual void draw(const Shader&) = 0;
    virtual GLuint update();
    virtual Shader& getDefaultShader();
    Color m_color;
};

inline GLuint Drawable::update()
{
    return 0;
}

//TODO remove
inline Shader& Drawable::getDefaultShader()
{
    static Shader shader = Shader();
    return shader;
}

#endif
