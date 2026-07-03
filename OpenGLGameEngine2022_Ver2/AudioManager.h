#include "Fmod/fmod.h"
#include "Fmod/fmod.hpp"

#pragma (lib, "fmod_vc.lib")
#pragma (lib, "fmodL_vc.lib")

using namespace FMOD;

#define MAX_SOUND_NUM 2

#define DEMO_BGM_INDEX 0
#define DEMO_SFX_INDEX 1

#pragma once
class AudioManager
{
public:
	AudioManager();
	~AudioManager();

private:
	static AudioManager* instance;
	System* system;
	Sound* sounds[MAX_SOUND_NUM];
	Channel* bgmChannel;
	Channel* sfxChannel;
	ChannelGroup* channelGroup;
	DSP* dspSmoothStop;

public:
	static AudioManager* GetInstance();

	void LoadAudio(const char* path, bool loop, int soundID);
	void PlaySFX(int soundID);
	void PlayBGM(int soundID);
	void setVolume(float value);


};

