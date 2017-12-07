#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/mat4x4.hpp>

class Camera
{
public:
    Camera();
    Camera(const Camera&);
    Camera(Camera&&);
    Camera& operator=(const Camera&);
    Camera& operator=(Camera&&);
    ~Camera() = default;
    const glm::vec2& getSize() const;
    void setSize(const glm::vec2&);
    const glm::vec2& getCenter() const;
    void setCenter(const glm::vec2&);
    void move(float, float);
    const glm::mat4& getProjection() const;
    const glm::mat4& getView() const;
private:
    friend class RenderTarget;
    void update();
    glm::vec2 m_size;
    glm::vec2 m_center;
    glm::mat4 m_projection;
    glm::mat4 m_view;
};

#endif
