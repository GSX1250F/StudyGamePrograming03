#include "BGSpriteComponent.h"
#include "BackGround.h"
#include <cmath>

BGSpriteComponent::BGSpriteComponent(Actor* owner , int drawOrder)
	: SpriteComponent(owner , drawOrder)
	,mScrollSpeed(Vector2::Zero)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	// 背景の位置を更新する。
	mBGSpritePos += mScrollSpeed * deltaTime;
	// ラッピング処理
	if (mBGSpritePos.x < -mTexWidth * mOwner->GetScale() * 0.5f)
	{
		mBGSpritePos.x += mTexWidth * 2.0f * mOwner->GetScale();
	}
	else if(mBGSpritePos.x > mTexWidth * mOwner->GetScale() * 1.5f)
	{
		mBGSpritePos.x -= mTexWidth * mOwner->GetScale() * 2.0f;
	}
	if (mBGSpritePos.y <= -mTexHeight * mOwner->GetScale() * 0.5f)
	{
		mBGSpritePos.y = mTexHeight* mOwner->GetScale() * 1.5f;
	}
	else if(mBGSpritePos.y >= mTexHeight * mOwner->GetScale() * 1.5f)
	{
		mBGSpritePos.y = -mTexHeight * mOwner->GetScale() * 0.5f;
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	// SpriteComponentのDrawをOverride。背景の位置で描画する。
	SDL_Rect r;
	r.w = nearbyint(mTexWidth * mOwner->GetScale());
	r.h = nearbyint(mTexHeight * mOwner->GetScale());
	r.x = nearbyint(mBGSpritePos.x - mTexWidth * 0.5f);
	r.y = nearbyint(mBGSpritePos.y - mTexHeight * 0.5f);

	SDL_RenderCopy(renderer, mTexture,nullptr,&r);

}
