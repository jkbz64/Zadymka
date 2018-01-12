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
    const glm::uvec2& size() const;
    const glm::vec2& center() const;
    void setCenter(const glm::vec2&);
    void setSize(const glm::uvec2&);
    void move(const glm::vec2&);
    const glm::mat4& getProjection() const;
    const glm::mat4& getView() const;
    void zoom(float);
private:
    friend class Graphics;
    friend class RenderTarget;
    void update();
    glm::uvec2 m_size;
    glm::vec2 m_center;
    glm::mat4 m_projection;
    glm::mat4 m_view;
};

#endif
