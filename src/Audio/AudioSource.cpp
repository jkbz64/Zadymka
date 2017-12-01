#include <Audio/AudioSource.hpp>
#include <AL/al.h>
#include <AL/alc.h>

AudioSource::AudioSource()
{
    alGenSources(1, &m_source);
    alSourcef(m_source, AL_PITCH, 1);
    alSourcef(m_source, AL_GAIN, 1);
    alSource3f(m_source, AL_POSITION, 0, 0, 0);
    alSource3f(m_source, AL_VELOCITY, 0, 0, 0);
    alSourcei(m_source, AL_LOOPING, AL_FALSE);
}

AudioSource::~AudioSource()
{
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

void AudioSource::setBuffer(AudioBuffer &buffer)
{
    m_currentBuffer = &buffer;
    alSourcei(m_source, AL_BUFFER, m_currentBuffer->m_buffer);
}
