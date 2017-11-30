#include <Audio/Audio.hpp>
#include <Lua.hpp>
#include <iostream>
#include <stb_vorbis.c>

namespace
{
    ALCdevice *device = nullptr;
    ALCcontext* context = nullptr;
    float globalVolume = 100.f;
    glm::vec3 listenerPosition(0.f, 0.f, 0.f);
    glm::vec3 listenerDirection(0.f, 0.f, -1.f);
    glm::vec3 listenerUpVector(0.f, 1.f, 0.f);
}

void Audio::registerModule()
{
    Lua::getState()["Audio"] = Lua::getState().create_table_with(
        "getDevices", &Audio::getDevices
    );
}

void Audio::init()
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
            std::cerr << "Failed to create audio context\n";
    }
    else
        std::cerr << "Failed to create audio context\n";
}

void Audio::destroy()
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

ALenum Audio::toAlFormat(short channels, short samples)
{
    bool stereo = (channels > 1);

    switch (samples)
    {
    case 16:
        if (stereo)
            return AL_FORMAT_STEREO16;
        else
            return AL_FORMAT_MONO16;
    case 8:
        if (stereo)
            return AL_FORMAT_STEREO8;
        else
            return AL_FORMAT_MONO8;
    default:
        return -1;
    }
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
