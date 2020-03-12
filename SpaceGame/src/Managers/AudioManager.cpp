#include "AudioManager.h"
#include "AEEngine.h"
#include "fmod_errors.h"

namespace AudioManager 
{
	static FMOD::System* _system;
	static FMOD_RESULT _result;

	FMOD::Sound* _sound;

	void Init()
	{
		// Create fmodsystem
		_system = NULL;
		ErrorCheck(FMOD::System_Create(&_system));

		// Init system
		ErrorCheck(_system->init(512, FMOD_INIT_NORMAL, nullptr));
	}

	void Update()
	{
		ErrorCheck(_system->update());
	}

	void Shutdown()
	{
		// Clean up.
		ErrorCheck(_sound->release());
		ErrorCheck(_system->release());
	}

	void ErrorCheck(FMOD_RESULT result)
	{
		AE_ASSERT(result == FMOD_OK && FMOD_ErrorString(result));
	}

	void Loadsound(const char* path)
	{
		_sound = nullptr;
		ErrorCheck(_system->createSound(path, FMOD_DEFAULT, nullptr, &_sound));
	}

	void UnLoadSound()
	{
		ErrorCheck(_sound->release());
	}

	void PlayOneShot()
	{
		ErrorCheck(_system->playSound(_sound, nullptr, false, nullptr));
	}
}
