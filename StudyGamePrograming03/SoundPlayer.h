#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <SDL_mixer.h>

class SoundPlayer
{
public:
	
	SoundPlayer(class Game* game);
	~SoundPlayer();

	bool Initialize();
	void UnloadData();
	void Shutdown();

	void Play();

	void AddSndCmpnt(class SoundComponent* sndC);
	void RemoveSndCmpnt(class SoundComponent* sndC);

	Mix_Chunk* GetChunk(const std::string& filename);
	
private:
	// 効果音のマップ
	std::unordered_map<std::string, Mix_Chunk*> mChunks;
	
	// サウンドコンポーネントの配列
	std::vector<class SoundComponent*> mSndCmpnts;	

	// Game
	class Game* mGame;
};

