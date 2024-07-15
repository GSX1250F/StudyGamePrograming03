#pragma once
#include "Component.h"
#include <SDL.h>
#include <string>
#include <SDL_mixer.h>

class SoundComponent : public Component
{
public:
	SoundComponent(class Actor* owner);
	~SoundComponent();

	virtual void SetPendingPlayChunk();

	virtual void SetChunk(Mix_Chunk* chunk) { mChunk = chunk; }
	Mix_Chunk* GetChunk() const { return mChunk; }
	
	void SetPlayable(bool value) { mPlayable = value; }
	bool GetPlayable() const { return mPlayable; }
	
private:
	bool mPlayable;
	Mix_Chunk* mChunk;	
};

