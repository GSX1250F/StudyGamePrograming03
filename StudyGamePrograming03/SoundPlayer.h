#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <SDL_mixer.h>

struct ChunkControl
{
	int channel;		// 0�`15, -1�͋󂢂Ă���Ƃ�����g���B
	Mix_Chunk* chunk;
	std::string control;	// play,pause,halt,resume,replay
	int repeat;			// 0:1�񂾂��B-1:�������[�v
};
struct MusicControl
{
	Mix_Music* music;
	int repeat;			// 0:1�񂾂��B-1:�������[�v
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
	// ���ʉ��̃}�b�v
	std::unordered_map<std::string, Mix_Chunk*> mChunks;
	
	// ���y�̃}�b�v
	std::unordered_map<std::string, Mix_Music*> mMusics;

	// �Đ��҂����ʉ��̔z��
	std::vector<ChunkControl> mPendingPlayChunks;

	// �Đ��҂����y�̔z��
	std::vector<MusicControl> mPendingPlayMusics;


	// Game
	class Game* mGame;
};

