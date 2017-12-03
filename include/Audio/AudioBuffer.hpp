#ifndef AUDIOBUFFER_HPP
#define AUDIOBUFFER_HPP
#include <string>
#include <sol/table.hpp>

class AudioBuffer
{
public:
    static void registerClass(sol::table);
    AudioBuffer();
    ~AudioBuffer();
    
    bool loadFromFile(const std::string&);
private:
    friend class AudioSource;
    unsigned int m_buffer;
};

#endif
