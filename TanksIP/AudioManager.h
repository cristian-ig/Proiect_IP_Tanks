#pragma once
#include <SDL_mixer.h>
#include <map>
#include <string>




namespace Engine {


class SoundEffect {
public:
	friend class AudioManager;
	// @param loops: If loops == -1, loop forever,otherwise play it loops+1 times 
	void play(int loops = 0);
private:
	Mix_Chunk* _chunk = nullptr;
};

class Music {
public:
	friend class AudioManager;
	// @param loops: If loops == -1, loop forever, otherwise play it loops times 
	void play(int loops = -1) { Mix_PlayMusic(_music, loops); }

	static void pause() { Mix_PauseMusic(); }

	static void stop() { Mix_HaltMusic(); }

	static void resume() { Mix_ResumeMusic(); }
private:
	Mix_Music* _music = nullptr;
};


class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	void init();
	void destroy();

	SoundEffect loadSoundEffect(const std::string& filePath);
	Music loadMusic(const std::string& filePath);
private:

	std::map<std::string, Mix_Chunk*> _effectMap; // Effects cache filepath and sound
	std::map<std::string, Mix_Music*> _musicMap; // Music cache

	bool _isInitialized = false;
};
}