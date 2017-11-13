#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <SFML/Graphics/View.hpp>
#include <Lua.hpp>

class Camera : public sf::View
{
public:
    static void registerClass();
    Camera();
    virtual ~Camera() = default;
};

#endif
