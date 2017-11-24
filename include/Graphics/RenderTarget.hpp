#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP
#include <Graphics/Camera.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Graphics/Drawable.hpp>

template<class T>
class RenderTarget
{
public:
    RenderTarget<T>();
    virtual ~RenderTarget<T>() = default;
    void drawRect(float, float, int, int, int, int, int, int);
    void drawText(const std::string&, float, float, const std::string&, unsigned int);
    void drawSprite(const std::string&, float, float, int, int);

    virtual void display() = 0;
    virtual void clear(unsigned int, unsigned int, unsigned int, unsigned int = 255u) = 0;
protected:
    Camera m_camera;
    struct RenderCache
    {
        GLuint m_cameraUBO;
        bool m_viewChanged;
    } m_renderCache;
};

#include <Graphics/RenderTarget.inl>

#endif
