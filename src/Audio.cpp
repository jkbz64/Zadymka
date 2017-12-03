#include <include/Audio.hpp>
#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <Audio/AudioBuffer.hpp>
#include <Audio/Sound.hpp>
#include <sol/state_view.hpp>

namespace
{
    ALCdevice *device = NULL;
    ALCcontext* context = NULL;
    float globalVolume = 100.f;
    glm::vec3 listenerPosition(0.f, 0.f, 0.f);
    glm::vec3 listenerDirection(0.f, 0.f, -1.f);
    glm::vec3 listenerUpVector(0.f, 1.f, 0.f);
}

sol::table Audio::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    AudioBuffer::registerClass(module);
    Sound::registerClass(module);
    return module;
}

bool Audio::init()
{
    device = alcOpenDevice(NULL);
    if(device)
    {
        context = alcCreateContext(device, NULL);
        if(context)
        {
            alcMakeContextCurrent(context);
            float orientation[] = {listenerDirection.x,
                                   listenerDirection.y,
                                   listenerDirection.z,
                                   listenerUpVector.x,
                                   listenerUpVector.y,
                                   listenerUpVector.z};
            alListenerf(AL_GAIN, globalVolume * 0.01f);
            alListener3f(AL_POSITION, listenerPosition.x, listenerPosition.y, listenerPosition.z);
            alListenerfv(AL_ORIENTATION, orientation);
        }
        else
        {
            std::cerr << "Failed to create audio context\n";
            return false;
        }
    }
    else
    {
        std::cerr << "Failed to create audio context\n";
        return false;
    }
    return true;
}

void Audio::deinit()
{
    alcMakeContextCurrent(NULL);
    if(context)
        alcDestroyContext(context);
    if(device)
        alcCloseDevice(device);
}

std::vector<std::string> Audio::getDevices()
{
    std::vector<std::string> devicesList;
    const ALchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
    const ALCchar *dev = devices, *next = devices + 1;
    size_t len = 0;

    fprintf(stdout, "Devices list:\n");
    fprintf(stdout, "----------\n");
    while (dev && *dev != '\0' && next && *next != '\0') {
        fprintf(stdout, "%s\n", dev);
        devicesList.emplace_back(std::string(dev));
        len = strlen(dev);
        dev += (len + 1);
        next += (len + 2);
    }
    fprintf(stdout, "----------\n");
    return devicesList;
}

void Audio::setGlobalVolume(float v)
{
    if(context)
        alListenerf(AL_GAIN, v * 0.01f);
    globalVolume = v;
}

float Audio::getGlobalVolume()
{
    return globalVolume;
}

void Audio::setPosition(glm::vec3 pos)
{
    if(context)
        alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
    listenerPosition = pos;
}

const glm::vec3& Audio::getPosition()
{
    return listenerPosition;
}

extern "C" int luaopen_Zadymka_Audio(lua_State* L)
{
    return sol::stack::call_lua(L, 1, Audio::createModule);
}