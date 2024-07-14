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

	virtual void Play();

	virtual void SetChunk(Mix_Chunk* chunk) { mChunk = chunk; }
	Mix_Chunk* GetChunk() const { return mChunk; }
	virtual void SetControl(std::string control) { mControl = control; }
	std::string GetControl() const { return mControl; }

	void SetPlayable(bool value) { mPlayable = value; }
	bool GetPlayable() const { return mPlayable; }
	
private:
	bool mPlayable;
	Mix_Chunk* mChunk;
	std::string mControl;
	
	
};

