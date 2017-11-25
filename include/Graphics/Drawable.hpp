#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include <Graphics/Shader.hpp>
#include <Graphics/Transformable.hpp>
#include <Graphics/Color.hpp>

class Window;

struct RenderDetails
{
    bool m_initialized{false};
    bool m_cameraSet{false};
    Shader m_shader;
    GLuint m_vao;
    GLuint m_verticesVBO{0};
    GLuint m_colorVBO{0};
    GLuint m_texCoordsVBO{0};
};

template<class T>
class Drawable : protected Transformable
{
public:
    static Shader& getShader();
    Drawable() = default;
    virtual ~Drawable() = default;
    void setColor(const Color&);
    const Color& getColor();
protected:
    friend class Window;
    friend class RenderTexture;
    virtual void draw() = 0;
    Color m_color;
    std::array<float, 24> m_colorArray;
    static RenderDetails m_renderDetails;
};

template<class T>
RenderDetails Drawable<T>::m_renderDetails;

template<class T>
Shader& Drawable<T>::getShader()
{
    return Drawable<T>::m_renderDetails.m_shader;
}

template<class T>
inline void Drawable<T>::setColor(const Color &color)
{
    m_color = color;
    const auto normalized = m_color.normalized();
    m_colorArray = {
        normalized[0], normalized[1], normalized[2], normalized[3],
        normalized[0], normalized[1], normalized[2], normalized[3],
        normalized[0], normalized[1], normalized[2], normalized[3],
        normalized[0], normalized[1], normalized[2], normalized[3],
        normalized[0], normalized[1], normalized[2], normalized[3],
        normalized[0], normalized[1], normalized[2], normalized[3],
    };
}

template<class T>
inline const Color& Drawable<T>::getColor()
{
    return m_color;
}

#endif
