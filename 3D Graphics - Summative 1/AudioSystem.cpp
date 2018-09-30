#include "AudioSystem.h"

AudioSystem::AudioSystem()
{
}

AudioSystem::~AudioSystem()
{
	SystemID->release();
}

bool AudioSystem::Init()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&SystemID);
	if (result != FMOD_OK)
		return false;

	result = SystemID->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK)
		return false;

	return true;
}

FMOD::Sound* AudioSystem::CreateSound(const std::string& FilePath, FMOD::Sound* Sound)
{
	FMOD_RESULT result;
	result = SystemID->createSound(FilePath.c_str(), FMOD_2D, 0, &Sound);
	if (result != FMOD_OK)
		std::cout << "Faild To Create Sound" << std::endl;
	return Sound;
}

void AudioSystem::PlaySound(FMOD::Sound* Sound)
{
	FMOD_RESULT result;
	result = SystemID->playSound(Sound, 0, false, 0);
	if (result != FMOD_OK)
		std::cout << "Faild To Play Sound" << std::endl;
}

FMOD::System * AudioSystem::GetID()
{
	return SystemID;
}
