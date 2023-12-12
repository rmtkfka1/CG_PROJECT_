#pragma once
#include "fmod.hpp"


enum sound
{
	BACKGROUND,
	HEARTBEAT,
	WALK,
	SCARE,
	CHASE,
	LOCKOPEN,
	SWAP,
	DOOR,
	TELEPORT,
	FLASH,
	RUN,
	START,
	FINDBODY,
	ENDINGSONG,
	GHOST_SCREAM,
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
	void Stop(sound song);
	bool endsong = false;
	bool real_end = false;
	bool realrealreal_end = false;
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

