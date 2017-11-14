#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include <Graphics/Shader.hpp>

class Window;

struct RenderDetails
{
    bool m_initialized{false};
    Shader m_shader;
    GLuint m_vao;
};

template<class T>
class Drawable
{
public:
    Drawable() = default;
    virtual ~Drawable() = default;
protected:
    friend class Window;
    virtual void draw(Window&) = 0;
    static RenderDetails m_renderDetails;
};

template<class T>
RenderDetails Drawable<T>::m_renderDetails;

#endif
