#include "SoundComponent.h"
#include "Game.h"
#include "Actor.h"
#include "SoundPlayer.h"
#include <string>

SoundComponent::SoundComponent(Actor* owner):Component(owner)
	,mChunk(nullptr)
	,mPlayable(true)
{
	mOwner->GetGame()->GetSoundPlayer()->AddSndCmpnt(this);
}

SoundComponent::~SoundComponent()
{
	mOwner->GetGame()->GetSoundPlayer()->RemoveSndCmpnt(this);
}

void SoundComponent::Play()
{
	if (mChunk && GetPlayable())
	{
		//Control = Play　（とりあえずこれだけ）
		if (mControl == "play")
		{
			Mix_PlayChannel(-1, mChunk, 0);            // 効果音再生
		}
		
		SetControl("");
	}
}

