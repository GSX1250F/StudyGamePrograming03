#include "BGSpriteComponent.h"
#include "BackGround.h"
#include <cmath>

BGSpriteComponent::BGSpriteComponent(Actor* owner , int drawOrder)
	: SpriteComponent(owner , drawOrder)
	,mScrollSpeed(Vector2::Zero)
	,mBGSpritePos(Vector2::Zero)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	// �w�i�̈ʒu���X�V����B
	mBGSpritePos += mScrollSpeed * deltaTime;
	// ���b�s���O����
	if (mBGSpritePos.x < - GetTexWidth() * mOwner->GetScale() * 0.5f)
	{
		mBGSpritePos.x += GetTexWidth() * 2.0f * mOwner->GetScale();
	}
	else if(mBGSpritePos.x > GetTexWidth() * mOwner->GetScale() * 1.5f)
	{
		mBGSpritePos.x -= GetTexWidth() * mOwner->GetScale() * 2.0f;
	}
	if (mBGSpritePos.y < - GetTexHeight() * mOwner->GetScale() * 0.5f)
	{
		mBGSpritePos.y = GetTexHeight() * mOwner->GetScale() * 1.5f;
	}
	else if(mBGSpritePos.y > GetTexHeight() * mOwner->GetScale() * 1.5f)
	{
		mBGSpritePos.y = - GetTexHeight() * mOwner->GetScale() * 0.5f;
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	// SpriteComponent��Draw��Override�B�w�i�̈ʒu�ŕ`�悷��B
	SDL_Rect r;
	r.w = nearbyint(GetTexWidth() * mOwner->GetScale());
	r.h = nearbyint(GetTexHeight() * mOwner->GetScale());
	r.x = nearbyint(mBGSpritePos.x - GetTexWidth() * 0.5f);
	r.y = nearbyint(mBGSpritePos.y - GetTexHeight() * 0.5f);

	SDL_RenderCopy(renderer, GetTexture(), nullptr, &r);

}
