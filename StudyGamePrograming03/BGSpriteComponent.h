#pragma once
#include "SpriteComponent.h"
#include "Math.h"

class BGSpriteComponent : public SpriteComponent
{
public:
	BGSpriteComponent(class Actor* owner, int drawOrder);
	
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void SetBGSpritePos(Vector2 pos) { mBGSpritePos = pos; }
	Vector2 GetBGSpritePos() { return mBGSpritePos; }
	void SetScrollSpeed(Vector2 speed) { mScrollSpeed = speed; }
	Vector2 GetScrollSpeed() { return mScrollSpeed; }

private:
	// 背景スプライトにはActorとは別に描画位置情報を持たせる。
	Vector2 mBGSpritePos;
	Vector2 mScrollSpeed;

};

