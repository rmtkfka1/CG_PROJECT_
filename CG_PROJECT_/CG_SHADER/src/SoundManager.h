#pragma once
#include "fmod.hpp"


enum sound
{
	TEST,
	HEARTBEAT,
	END
};


class SoundManager
{


public:

	static SoundManager* GetInstance()
	{
		static SoundManager MM;
		return &MM;
	}


	void Init();
	void Update();
	void Play(sound song);


private:

	void load();

	FMOD::System* ssystem;
	FMOD::Sound* fsound[END];
	FMOD::Channel* channel = 0;
	FMOD_RESULT result;
	void* extradriverdata = 0;

	std::unordered_map<sound, bool> soundPlayingStatus;  
	std::unordered_map<sound, FMOD::Channel*> playingChannels; 


};

