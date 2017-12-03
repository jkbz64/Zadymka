#ifndef AUDIO_HPP
#define AUDIO_HPP
#include <sol/table.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <string>

namespace Audio
{
    sol::table createModule(sol::this_state);
    bool init();
    void deinit();
    std::vector<std::string> getDevices();
    void setGlobalVolume(float);
    float getGlobalVolume();
    void setPosition(glm::vec3);
    const glm::vec3& getPosition();
}

extern "C"
{
    struct lua_State;
}

extern "C" int luaopen_Zadymka_Audio(lua_State*);

#endif
