#include "pch.h"
#include "SoundManager.h"


void SoundManager::Init()
{
    result = FMOD::System_Create(&ssystem);

    if (result != FMOD_OK)
        exit(0);

    ssystem->init(32, FMOD_INIT_NORMAL, extradriverdata);

    load();
}

void SoundManager::Update()
{
    ssystem->update();

    for (auto& entry : soundPlayingStatus)
    {
        sound song = entry.first; // song 
        bool& isPlaying = entry.second; // bool

        FMOD::Channel* channel = playingChannels[song]; //�����÷������� ���� ä���� �ּ� �����ͼ�

        if (channel)
        {
            // ä���� ���� ��� ������ Ȯ��
            bool channelPlaying;
            channel->isPlaying(&channelPlaying);

            if (!channelPlaying)
            {
                // ����� ������ ��, ���� ������Ʈ
                isPlaying = false;
                playingChannels[song] = nullptr;
            }
        }
    }


}

void SoundManager::Play(sound song)
{
  
    if (soundPlayingStatus[song] == false)
    {

        ssystem->playSound(fsound[song], 0, false, &channel);

        soundPlayingStatus[song] = true;

        playingChannels[song] = channel;

    }



}

void SoundManager::load()
{
    ssystem->createSound("res/sound/sound.mp3", FMOD_LOOP_NORMAL, 0, &fsound[TEST]);
    ssystem->createSound("res/sound/heartbeat.mp3", FMOD_DEFAULT, 0, &fsound[HEARTBEAT]);
}