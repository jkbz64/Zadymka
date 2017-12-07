#include <Audio/Sound.hpp>
#include <AL/al.h>
#include <AL/alc.h>

Sound::Sound() :
    AudioSource()
{

}

Sound::~Sound()
{

}

void Sound::play()
{
    alSourcePlay(m_source);
}

void Sound::pause()
{
    //TODO
}

void Sound::stop()
{
    //TODO
}