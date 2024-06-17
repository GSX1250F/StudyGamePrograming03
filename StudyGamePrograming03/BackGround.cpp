#include "BackGround.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

BackGround::BackGround(Game* game) : Actor(game)
{
	LoadData();
}

void BackGround::UpdateActor(float deltaTime)
{
	// ŠeBGSpriteComponent‚ðXV
	for (auto sprite : mBGsprites)
	{
		sprite->Update(deltaTime);
	}
}

void BackGround::LoadData()
{
	// BGSpriteComponent‚ðì¬‚µA”z—ñ‚É’Ç‰Á‚·‚éB
	//”wŒi1‚Â–Ú
	BGSpriteComponent* bgsc = new BGSpriteComponent(this, 5);
	bgsc->SetTexture(GetGame()->GetTexture("Assets/Farback01.png"));
	bgsc->SetBGSpritePos(Vector2(GetGame()->mWindowWidth * 0.5f, GetGame()->mWindowHeight * 0.5f));
	bgsc->SetScrollSpeed(Vector2(-10.0f , 0.0f));
	mBGsprites.emplace_back(bgsc);
	
	//”wŒi2‚Â–Ú
	bgsc = new BGSpriteComponent(this, 5);
	bgsc->SetTexture(GetGame()->GetTexture("Assets/Farback02.png"));
	bgsc->SetBGSpritePos(Vector2(GetGame()->mWindowWidth * 0.5f + bgsc->GetTexWidth(), GetGame()->mWindowHeight * 0.5f));
	bgsc->SetScrollSpeed(Vector2(-10.0f, 0.0f));
	mBGsprites.emplace_back(bgsc);

	//”wŒi3‚Â–Ú
	bgsc = new BGSpriteComponent(this, 10);
	bgsc->SetTexture(GetGame()->GetTexture("Assets/Stars.png"));
	bgsc->SetBGSpritePos(Vector2(GetGame()->mWindowWidth * 0.5f, GetGame()->mWindowHeight * 0.5f));
	bgsc->SetScrollSpeed(Vector2(-20.0f, 0.0f));
	mBGsprites.emplace_back(bgsc);

	//”wŒi4‚Â–Ú
	bgsc = new BGSpriteComponent(this, 10);
	bgsc->SetTexture(GetGame()->GetTexture("Assets/Stars.png"));
	bgsc->SetBGSpritePos(Vector2(GetGame()->mWindowWidth * 0.5f + bgsc->GetTexWidth(), GetGame()->mWindowHeight * 0.5f));
	bgsc->SetScrollSpeed(Vector2(-20.0f, 0.0f));
	mBGsprites.emplace_back(bgsc);
}

