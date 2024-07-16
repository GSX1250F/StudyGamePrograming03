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

	virtual void SetPendingPlayChunk(int channel, std::string control);

	virtual void SetChunk(Mix_Chunk* chunk) { mChunk = chunk; }
	virtual void SetMusic(Mix_Music* music) { mMusic = music; }
	Mix_Chunk* GetChunk() const { return mChunk; }
	Mix_Music* GetMusic() const { return mMusic; }
	
	void SetPlayable(bool value) { mPlayable = value; }
	bool GetPlayable() const { return mPlayable; }
	
private:
	bool mPlayable;
	Mix_Chunk* mChunk;
	Mix_Music* mMusic;
};

