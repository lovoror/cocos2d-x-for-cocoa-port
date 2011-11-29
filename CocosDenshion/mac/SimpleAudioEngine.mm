#include "SimpleAudioEngine.h"

namespace CocosDenshion {

SimpleAudioEngine::SimpleAudioEngine() {
}

SimpleAudioEngine::~SimpleAudioEngine() {
}

SimpleAudioEngine* SimpleAudioEngine::sharedEngine() {
	static SimpleAudioEngine s_SharedEngine;
	return &s_SharedEngine;
}

void SimpleAudioEngine::end() {

}

void SimpleAudioEngine::setResource(const char* pszZipFileName) {
}

//////////////////////////////////////////////////////////////////////////
// BackgroundMusic
//////////////////////////////////////////////////////////////////////////

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath,
		bool bLoop) {
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData) {
}

void SimpleAudioEngine::pauseBackgroundMusic() {
}

void SimpleAudioEngine::resumeBackgroundMusic() {
}

void SimpleAudioEngine::rewindBackgroundMusic() {
}

bool SimpleAudioEngine::willPlayBackgroundMusic() {
    return true;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying() {
    return true;
}

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath,
		bool bLoop) {
    return true;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId) {
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath) {
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath) {
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath) {
}

//////////////////////////////////////////////////////////////////////////
// volume interface
//////////////////////////////////////////////////////////////////////////

float SimpleAudioEngine::getBackgroundMusicVolume() {
    return 1;
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume) {
}

float SimpleAudioEngine::getEffectsVolume() {
    return 1;
}

void SimpleAudioEngine::setEffectsVolume(float volume) {
}


} // end of namespace CocosDenshion
