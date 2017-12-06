#include <Audio/AudioBuffer.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <Audio/stb_vorbis/stb_vorbis.hpp>

void AudioBuffer::registerClass(sol::table module)
{
    module.new_usertype<AudioBuffer>("AudioBuffer", sol::constructors<AudioBuffer()>(),
                                              "loadFromFile", &AudioBuffer::loadFromFile
    );
}

AudioBuffer::AudioBuffer()
{
    alGenBuffers(1, &m_buffer);
}

AudioBuffer::~AudioBuffer()
{
    if(m_buffer)
        alDeleteBuffers(1, &m_buffer);
}

bool AudioBuffer::loadFromFile(const std::string &filename)
{
    ALint channels = 2, sampleRate = 44100, samples;
    ALshort* data;
    samples = stb_vorbis_decode_filename(filename.c_str(), &channels, &sampleRate, &data);
    if(data)
        alBufferData(m_buffer, AL_FORMAT_STEREO16, data, samples * 2 * sizeof(short), sampleRate);
    else
        return false;
    return true;
}


