#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

class Transformable
{
public:
    Transformable();
    Transformable(const Transformable&);
    Transformable& operator=(const Transformable&);
    Transformable(Transformable&&);
    Transformable& operator=(Transformable&&);
    virtual ~Transformable() = default;
    void translate(const glm::vec2&);
    void translateBy(float, float);
    void scale(float, float);
    void rotate(float);
    const glm::mat4& getModel() const;
protected:
    glm::vec2 m_translation;
    glm::vec2 m_scale;
    float m_rotation;
    mutable bool m_modified;
    mutable glm::mat4 m_model;
};

#endif
