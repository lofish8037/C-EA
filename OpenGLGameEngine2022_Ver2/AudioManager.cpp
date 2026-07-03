#include "AudioManager.h"
#include <iostream>

using namespace std;

AudioManager* AudioManager::instance = nullptr;


AudioManager::AudioManager()
{
	System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, 0);
	bgmChannel = nullptr;
	sfxChannel = nullptr;
	channelGroup = nullptr;
	dspSmoothStop = nullptr;
	for (int i = 0; i < MAX_SOUND_NUM; i++) {
		sounds[i] = nullptr;
	}

}


AudioManager::~AudioManager()
{
	for (int i = 0; i < MAX_SOUND_NUM; i++) {
		sounds[i]->release();
	}
	system->release();
}

AudioManager* AudioManager::GetInstance() {
	if (instance == nullptr) {
		instance = new AudioManager();
	}
	return instance;
}

void AudioManager::LoadAudio(const char* path, bool loop, int soundID) {

	if (soundID >= MAX_SOUND_NUM) {
		std::cout << "[ERROR] Please increase MAX_SOUND_NUM" << std::endl;
		return;
	}

	FMOD_MODE mode = (loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
	system->createSound(path, mode, 0, &sounds[soundID]);
}

void AudioManager::PlayBGM(int soundID) {
	if (soundID >= MAX_SOUND_NUM) {
		std::cout << "[ERROR] soundID NOT EXIST" << std::endl;
		return;
	}
	bgmChannel->stop();
	system->playSound(sounds[soundID], channelGroup, false, &bgmChannel);
}

void AudioManager::PlaySFX(int soundID) {
	if (soundID >= MAX_SOUND_NUM) {
		std::cout << "[ERROR] soundID NOT EXIST" << std::endl;
		return;
	}

	system->playSound(sounds[soundID], channelGroup, false, &sfxChannel);
}

void AudioManager::setVolume(float value) {
	bgmChannel->setVolume(value);
	sfxChannel->setVolume(value);
}


