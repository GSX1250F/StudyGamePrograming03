#include "SoundComponent.h"
#include "Game.h"
#include "Actor.h"
#include "SoundPlayer.h"
#include <string>

SoundComponent::SoundComponent(Actor* owner):Component(owner)
	,mChunk(nullptr)
	,mPlayable(true)
{}

SoundComponent::~SoundComponent()
{}

void SoundComponent::SetPendingPlayChunk(int channel, std::string control)
{
	ChunkControl chunkCtl;
	chunkCtl.channel = channel;
	chunkCtl.chunk = mChunk;
	chunkCtl.control = control;
	chunkCtl.repeat = 0;
	mOwner->GetGame()->GetSoundPlayer()->SetPendingPlayChunk(chunkCtl);
}

