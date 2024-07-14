#pragma once
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>
#include "SoundComponent.h"

class SoundPlayer
{
public:
	
	SoundPlayer(class Game* game);
	~SoundPlayer();

	bool Initialize();
	void UnloadData();
	void Shutdown();

	void Play();

	void AddSndCmpnt(SoundComponent* sndC);
	void RemoveSndCmpnt(SoundComponent* sndC);

	Mix_Chunk* GetAliasName(std::string fileName);
	void SetSoundControl(Mix_Chunk* aliasName, std::string control);
	std::string ControlGetStatus(int id);
	void ControlPlay(int id);
	void ControlReplay(int id);
	void ControlPause(int id);
	void ControlStop(int id);
	void ControlResume(int id);
	void ControlClose(Mix_Chunk* aliasName);

private:
	std::vector<Mix_Chunk*> mAliasNames;
	std::vector<std::string> mControls;		//"play","replay","resume","stop","pause","delete"
	std::vector<class SoundComponent*> mSndCmpnts;	
};

