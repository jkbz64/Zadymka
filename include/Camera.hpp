#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Scriptable.hpp>
#include <SFML/Graphics/View.hpp>

class Camera : public sf::View, public Scriptable<Camera>
{
public:
    static void exposeToLua();
    Camera();
    virtual ~Camera() = default;
};

#endif
