#ifndef AUDIO_HPP
#define AUDIO_HPP
#include <sol/table.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <string>

struct Audio
{
    static sol::table createModule(sol::this_state);
    static bool init();
    static void deinit();
    static std::vector<std::string> getDevices();
    static void setGlobalVolume(float);
    static float getGlobalVolume();
    static void setPosition(glm::vec3);
    static const glm::vec3& getPosition();
};

extern "C"
{
    struct lua_State;
}

extern "C" int luaopen_Zadymka_Audio(lua_State*);

#endif
