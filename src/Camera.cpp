#include <Camera.hpp>

void Camera::registerClass()
{
    Lua::getState().new_usertype<Camera>("Camera",
                                         sol::constructors<Camera()>(),
                                         "setCenter", static_cast<void(Camera::*)(float, float)>(&Camera::setCenter),
                                         "getCenter", [](Camera& camera) { return std::make_tuple(camera.getCenter().x, camera.getCenter().y); },
                                         "setSize", static_cast<void(Camera::*)(float, float)>(&Camera::setSize),
                                         "getSize", [](Camera& camera) { return std::make_tuple(camera.getSize().x, camera.getSize().y); },
                                         "setRotation", &Camera::setRotation,
                                         "getRotation", &Camera::getRotation,
                                         "move", static_cast<void(Camera::*)(float, float)>(&Camera::move),
                                         "zoom", &Camera::zoom
   );
}

Camera::Camera() :
    sf::View()
{
    setSize(800, 600);
    setCenter(400, 300);
}
