#pragma once
#include "SoundComponent.h"
#include <vector>

class SomeSoundComponent :public SoundComponent
{
public:
	SomeSoundComponent(class Actor* owner);

	void SetSomeChunks(std::vector<Mix_Chunk*> chunks) { mSomeChunks = chunks; }
	void SetChunkFromId(int id) { SetChunk(mSomeChunks[id]); }

private:
	std::vector<Mix_Chunk*> mSomeChunks;		// ‚·‚×‚Ä‚ÌŒø‰Ê‰¹
};

