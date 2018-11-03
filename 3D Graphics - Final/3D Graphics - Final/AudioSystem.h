#pragma once
#ifndef __AUDIOSYSTEM_H__
#define __AUDIOSYSTEM_H__

//fmod
#include <fmod.hpp>
#include <iostream>

class AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();

	bool Init();

	FMOD::Sound* CreateSound(const std::string& FilePath, FMOD::Sound* Sound, unsigned int Mode);
	void PlaySound(FMOD::Sound* Sound);
	void PlaySFX();
	FMOD::System* GetID();
private:

	FMOD::System* SystemID;
	//Sounds
	FMOD::Sound* fxThump;
	FMOD::Sound* trackBackground;
};
#endif // !__AUDIOSYSTEM_H__
