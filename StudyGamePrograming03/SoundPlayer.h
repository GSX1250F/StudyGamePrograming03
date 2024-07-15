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

	Mix_Chunk* GetChunk(const std::string& filename);
	Mix_Music* GetMusic(const std::string& filename);

	void SetPendingPlayChunk(Mix_Chunk* chunk);
	void SetPendingPlayMusic(Mix_Music* music);

private:
	// 効果音のマップ
	std::unordered_map<std::string, Mix_Chunk*> mChunks;
	
	// 音楽のマップ
	std::unordered_map<std::string, Mix_Music*> mMusics;

	// 再生待ち効果音の配列
	std::vector<Mix_Chunk*> mPendingPlayChunks;

	// 再生待ち音楽の配列
	std::vector<Mix_Music*> mPendingPlayMusics;


	// Game
	class Game* mGame;
};

