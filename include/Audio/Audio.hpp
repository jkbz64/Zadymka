#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <string>

namespace Audio
{
    void registerModule();
    bool init();
    void destroy();
    std::vector<std::string> getDevices();
    void setGlobalVolume(float);
    float getGlobalVolume();
    void setPosition(glm::vec3);
    const glm::vec3& getPosition();
}

#endif
