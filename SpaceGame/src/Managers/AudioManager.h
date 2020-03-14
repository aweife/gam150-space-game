/*********************************************************************************
* \file			AudioManager.h
* \brief		API to FMOD to play sounds in the game
* \author		Ang Wei Feng, 100% Code Contribution
*
*				Provide an easy interface to allow us to load and play sounds.
*               Extremely lightweight, scaling to the demands of our game
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
                or disclosure of this file or its contents without the prior
                written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "fmod.hpp"
#include <string>

namespace AudioManager
{
    void Init();
    void Update();
    void Shutdown();
    void ErrorCheck(FMOD_RESULT result);

    void LoadSound(const std::string& path, bool loop = false);
    void UnLoadSound(const std::string& path);
    void UnLoadAllSounds();
    void PlayOneShot(const std::string& path, float volume = 1.0f);
}
