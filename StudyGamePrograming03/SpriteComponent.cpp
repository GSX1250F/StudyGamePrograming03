#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include <cmath>

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner),
	mTexture(nullptr),
	mDrawOrder(drawOrder),
	mTexWidth(0),
	mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture && mOwner->GetState() != mOwner->EPaused)
	{
		SDL_Rect r;
		// 高さと幅を所有アクターのスケールに合わせる
		r.w = nearbyint(mTexWidth * mOwner->GetScale());
		r.h = nearbyint(mTexHeight * mOwner->GetScale());
		r.x = nearbyint(mOwner->GetPosition().x - r.w / 2);
		r.y = nearbyint(mOwner->GetPosition().y - r.h / 2);

		SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, -Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
	}


}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// 高さと幅を設定
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
	// 高さと幅の平均をActorの直径とする。
	mOwner->SetRadius((mTexWidth + mTexHeight) * 0.25f);
}