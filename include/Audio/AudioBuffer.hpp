#ifndef AUDIOBUFFER_HPP
#define AUDIOBUFFER_HPP
#include <string>

class AudioBuffer
{
public:
    AudioBuffer();
    ~AudioBuffer();
    
    bool loadFromFile(const std::string&);
private:
    friend class AudioSource;
    unsigned int m_buffer;
};

#endif
