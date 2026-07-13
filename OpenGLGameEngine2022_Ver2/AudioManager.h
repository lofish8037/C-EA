#include "Fmod/fmod.h"
#include "Fmod/fmod.hpp"

#pragma (lib, "fmod_vc.lib")
#pragma (lib, "fmodL_vc.lib")

using namespace FMOD;

#define MAX_SOUND_NUM 18

#define DEMO_BGM_INDEX 0
#define DEMO_SlimeBgm_INDEX 1
#define DEMO_CoffinBgm_INDEX 2
#define DEMO_BossBgm_INDEX 3
#define DEMO_EndBgm_INDEX 4

#define DEMO_SFX_INDEX 5
#define DEMO_BubbleDistory_INDEX 6
#define DEMO_BubbleShoot_INDEX 7
#define DEMO_Fire_INDEX 8
#define DEMO_Ice_INDEX 9
#define DEMO_Change_INDEX 10
#define DEMO_SlimeAtk_INDEX 11
#define DEMO_CoffinAtk_INDEX 12
#define DEMO_BossAtk_INDEX 13
#define DEMO_Blind_INDEX 14
#define DEMO_AtkInvalid_INDEX 15
#define DEMO_Fail_INDEX 16
#define DEMO_Shield_INDEX 17

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

