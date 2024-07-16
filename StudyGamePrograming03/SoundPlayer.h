#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <SDL_mixer.h>

struct ChunkControl
{
	int channel;		// 0～15, -1は空いているところを使う。
	Mix_Chunk* chunk;
	std::string control;	// play,pause,halt,resume,replay
	int repeat;			// 0:1回だけ。-1:無限ループ
};
struct MusicControl
{
	Mix_Music* music;
	int repeat;			// 0:1回だけ。-1:無限ループ
};

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

	void SetPendingPlayChunk(ChunkControl chunkCtl);	
	void SetPendingPlayMusic(MusicControl musicCtl);

private:
	// 効果音のマップ
	std::unordered_map<std::string, Mix_Chunk*> mChunks;
	
	// 音楽のマップ
	std::unordered_map<std::string, Mix_Music*> mMusics;

	// 再生待ち効果音の配列
	std::vector<ChunkControl> mPendingPlayChunks;

	// 再生待ち音楽の配列
	std::vector<MusicControl> mPendingPlayMusics;


	// Game
	class Game* mGame;
};

