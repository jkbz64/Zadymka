#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <glm/vec3.hpp>
#include <vector>
#include <string>
#include <AL/al.h>
#include <AL/alc.h>

namespace Audio
{
    void registerModule();
    void init();
    void destroy();
    std::vector<std::string> getDevices();
    ALenum toAlFormat(short, short);
    void setGlobalVolume(float);
    float getGlobalVolume();
    void setPosition(glm::vec3);
    const glm::vec3& getPosition();
}

#endif
