#ifndef AUDIOBUFFER_HPP
#define AUDIOBUFFER_HPP

class AudioBuffer
{
public:
    enum class Status
    {
        Stopped,
        Paused,
        Playing
    };
    static void registerClass();
    AudioBuffer();
    ~AudioBuffer();
};





#endif
