#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include <Graphics/Shader.hpp>
#include <Graphics/Transformable.hpp>

class Window;

struct RenderDetails
{
    bool m_initialized{false};
    Shader m_shader;
    GLuint m_vao;
    GLuint m_verticesVBO{0};
    GLuint m_colorVBO{0};
};

template<class T>
class Drawable : protected Transformable
{
public:
    static Shader& getShader();
    Drawable() = default;
    virtual ~Drawable() = default;
protected:
    friend class Window;
    virtual void draw(Window&) = 0;
    static RenderDetails m_renderDetails;
};

template<class T>
RenderDetails Drawable<T>::m_renderDetails;

template<class T>
Shader& Drawable<T>::getShader()
{
    return Drawable<T>::m_renderDetails.m_shader;
}

#endif
