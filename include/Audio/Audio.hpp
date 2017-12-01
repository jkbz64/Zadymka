#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <glm/vec3.hpp>
#include <vector>
#include <string>

namespace Audio
{
    void registerModule();
    bool init();
    void destroy();
    std::vector<std::string> getDevices();
    int toAlFormat(short, short);
    void setGlobalVolume(float);
    float getGlobalVolume();
    void setPosition(glm::vec3);
    const glm::vec3& getPosition();
}

#endif
