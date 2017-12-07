#include <Graphics/Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Camera::registerClass(sol::table module)
{
    module.new_usertype<Camera>("Camera",
                                         sol::constructors<Camera(), Camera(const Camera&)>(),
                                         "setCenter", &Camera::setCenter,
                                         "getCenter", &Camera::getCenter,
                                         "setSize", &Camera::setSize,
                                         "getSize", &Camera::getSize,
                                         "move", &Camera::move
   );
}

Camera::Camera() :
    m_size(800.f, 600.f),
    m_center(0.f, 0.f)
{
    update();
}

Camera::Camera(const Camera &other) :
    m_size(other.m_size),
    m_center(other.m_center)
{
    update();
}

Camera::Camera(Camera&& other) :
    m_size(std::move(other.m_size)),
    m_center(std::move(other.m_center))
{
    update();
}

Camera& Camera::operator=(const Camera& other)
{
    if(this != &other)
    {
        m_size = other.m_size;
        m_center = other.m_center;
        update();
    }
    return *this;
}

Camera& Camera::operator=(Camera&& other)
{
    if(this != &other)
    {
        m_size = std::move(other.m_size);
        m_center = std::move(other.m_center);
        update();
    }
    return *this;
}

const glm::vec2& Camera::getSize() const
{
    return m_size;
}

void Camera::setSize(const glm::vec2 &size)
{
    m_size = size;
    update();
}

const glm::vec2& Camera::getCenter() const
{
    return m_center;
}

void Camera::setCenter(const glm::vec2 &center)
{
    m_center = center;
    update();
}

void Camera::move(float dx, float dy)
{
    m_center.x += dx;
    m_center.y += dy;
    update();
}

const glm::mat4& Camera::getView() const
{
    return m_view;
}

const glm::mat4& Camera::getProjection() const
{
    return m_projection;
}

void Camera::update()
{
    m_projection = glm::ortho(0.f, m_size.x, m_size.y, 0.f, 0.1f, 100.f);
    m_view = glm::lookAt(glm::vec3(m_center.x - m_size.x / 2.f, m_center.y - m_size.y / 2.f, 1.f),
                         glm::vec3(m_center.x - m_size.x / 2.f, m_center.y - m_size.y / 2.f, 0.f),
                         glm::vec3(0.f, 1.f, 0.f));
}
