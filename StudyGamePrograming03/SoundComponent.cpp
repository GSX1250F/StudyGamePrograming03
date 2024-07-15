#include "SoundComponent.h"
#include "Game.h"
#include "Actor.h"
#include "SoundPlayer.h"
#include <string>

SoundComponent::SoundComponent(Actor* owner):Component(owner)
	,mChunk(nullptr)
	,mPlayable(true)
	,mPendingRemove(false)
{
	mOwner->GetGame()->GetSoundPlayer()->AddSndCmpnt(this);
}

SoundComponent::~SoundComponent()
{
	SetPendingRemove(true);
	//mOwner->GetGame()->GetSoundPlayer()->RemoveSndCmpnt(this);
}

void SoundComponent::Play()
{
	if (mChunk && GetPlayable())
	{
		//Control = Play@i‚Æ‚è‚ ‚¦‚¸‚±‚ê‚¾‚¯j
		if (mControl == "play")
		{
			Mix_PlayChannel(-1, mChunk, 0);            // Œø‰Ê‰¹Ä¶
		}
		
		SetControl("");
	}
}

