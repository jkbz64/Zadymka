#ifndef AUDIOSOURCE_HPP
#define AUDIOSOURCE_HPP
#include <glm/vec3.hpp>
#include <Audio/AudioBuffer.hpp>

class AudioSource
{
public:
    AudioSource();
    virtual ~AudioSource();
    enum class Status
    {
        Stopped,
        Paused,
        Playing
    };
    
    void setVolume(float);
    float getVolume() const;

    void setPosition(const glm::vec3&);
    const glm::vec3& getPosition();
    
    void setBuffer(AudioBuffer&);
    
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
protected:
    float m_volume;
    glm::vec3 m_position;
    unsigned int m_source;
    AudioBuffer* m_currentBuffer;
};

#endif
