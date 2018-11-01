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

	FMOD::Sound* CreateSound(const std::string& FilePath, FMOD::Sound* Sound);
	void PlaySound(FMOD::Sound* Sound);
	FMOD::System* GetID();
private:
	FMOD::System* SystemID;
};
#endif // !__AUDIOSYSTEM_H__
