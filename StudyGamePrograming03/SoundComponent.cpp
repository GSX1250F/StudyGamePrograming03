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

void SoundComponent::SetPendingPlayChunk(int channel, int repeat)
{
	ChunkControl chunkCtl;
	chunkCtl.channel = channel;
	chunkCtl.chunk = mChunk;
	chunkCtl.repeat = repeat;
	mOwner->GetGame()->GetSoundPlayer()->SetPendingPlayChunk(chunkCtl);
}

