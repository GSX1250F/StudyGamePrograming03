#pragma once
#include <string>
#include <vector>
#include <SDL.h>

class SoundPlayer
{
public:
	
	SoundPlayer(class Game* game);
	~SoundPlayer();

	bool Initialize();
	void Shutdown();
	void UnloadData();

	void Play();

	void AddSndCmpnt(SoundComponent* sndC);
	void RemoveSndCmpnt(SoundComponent* sndC);

	Mix_Chunk* GetAliasName(std::string fileName);
	void SetSoundControl(Mix_Chunk* aliasName, std::string control);


private:
	std::vector<Mix_Chunk*> mAliasNames;
	std::vector<string> mControls;		//"play","replay","resume","stop","pause","delete"
	std::vector<class SoundComponent*> mSndCmpnts;	
};

