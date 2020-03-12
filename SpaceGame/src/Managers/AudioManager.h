#pragma once

#include "fmod.hpp"

namespace AudioManager
{
    void Init();
    void Update();
    void Shutdown();
    void ErrorCheck(FMOD_RESULT result);

    void Loadsound(const char*);
    void UnLoadSound();
    void PlayOneShot();
}
