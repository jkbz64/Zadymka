#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

class Transformable
{
public:
    static void registerClass();
    Transformable();
    virtual ~Transformable() = default;
    void setPosition(float, float);
    const glm::vec2& getPosition();
    void setSize(unsigned int, unsigned int);
    const glm::vec2& getSize();
    void setRotation(float);
    float getRotation();
    const glm::mat4& getModel();
private:
    bool m_modified;
    glm::vec2 m_position;
    glm::vec2 m_size;
    float m_rotation;
    glm::mat4 m_model;
};

#endif
