#include <Audio/Sound.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <Lua.hpp>

void Sound::registerClass()
{
    Lua::getState().new_usertype<Sound>("Sound", sol::constructors<Sound()>(),
                                        "getPosition", &Sound::getPosition,
                                        "setPosition", &Sound::setPosition,
                                        "setBuffer", &Sound::setBuffer,
                                        "play", &Sound::play,
                                        "pause", &Sound::pause,
                                        "stop", &Sound::stop
    );
}

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