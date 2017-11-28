#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <Lua.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
public:
    static void registerClass();
    Camera();
    Camera(const Camera&);
    Camera(Camera&&);
    Camera& operator=(const Camera&);
    Camera& operator=(Camera&&);
    ~Camera() = default;
    const glm::vec2& getSize();
    void setSize(const glm::vec2&);
    const glm::vec2& getCenter();
    void setCenter(const glm::vec2&);
    void move(float, float);
    const glm::mat4& getProjection();
    const glm::mat4& getView();
private:
    friend class RenderTarget;
    void update();
    glm::vec2 m_size;
    glm::vec2 m_center;
    glm::mat4 m_projection;
    glm::mat4 m_view;
};

#endif
