#include <Audio/AudioSource.hpp>
#include <AL/al.h>
#include <AL/alc.h>

AudioSource::AudioSource()
{
    alGenSources(1, &m_source);
    alSourcei(m_source, AL_BUFFER, 0);
}

AudioSource::~AudioSource()
{
    alSourcei(m_source, AL_BUFFER, 0);
    alDeleteSources(1, &m_source);
}

void AudioSource::setVolume(float volume)
{
    m_volume = volume;
    alSourcef(m_source, AL_GAIN, volume * 0.01f);
}

float AudioSource::getVolume() const
{
    return m_volume;
}

void AudioSource::setPosition(const glm::vec3 &position)
{
    m_position = position;
    alSource3f(m_source, AL_POSITION, position.x, position.y, position.z);
}

const glm::vec3& AudioSource::getPosition()
{
    return m_position;
}
