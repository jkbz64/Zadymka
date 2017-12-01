#ifndef AUDIOSOURCE_HPP
#define AUDIOSOURCE_HPP
#include <glm/vec3.hpp>

class AudioSource
{
public:
    AudioSource();
    ~AudioSource();

    void setVolume(float);
    float getVolume() const;

    void setPosition(const glm::vec3&);
    const glm::vec3& getPosition();
protected:
    float m_volume;
    glm::vec3 m_position;
    unsigned int m_source;
};

#endif
