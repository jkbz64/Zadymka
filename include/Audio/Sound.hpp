#ifndef SOUND_HPP
#define SOUND_HPP
#include <Audio/AudioSource.hpp>

class Sound : public AudioSource
{
public:
    static void registerClass();
    Sound();
    virtual ~Sound();
    
    virtual void play() override;
    virtual void pause() override;
    virtual void stop() override;
};


#endif
