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
	// �eBGSpriteComponent���X�V
	for (auto sprite : mBGsprites)
	{
		sprite->Update(deltaTime);
	}
}

void BackGround::LoadData()
{
	// BGSpriteComponent���쐬���A�z��ɒǉ�����B
	//�w�i1��
	BGSpriteComponent* bgsc = new BGSpriteComponent(this, 5);
	bgsc->SetTexture(GetGame()->GetTexture("Assets/Farback01.png"));
	bgsc->SetBGSpritePos(Vector2(GetGame()->mWindowWidth * 0.5f, GetGame()->mWindowHeight * 0.5f));
	bgsc->SetScrollSpeed(Vector2(-10.0f , 0.0f));
	mBGsprites.emplace_back(bgsc);
	
	//�w�i2��
	bgsc = new BGSpriteComponent(this, 5);
	bgsc->SetTexture(GetGame()->GetTexture("Assets/Farback02.png"));
	bgsc->SetBGSpritePos(Vector2(GetGame()->mWindowWidth * 0.5f + bgsc->GetTexWidth(), GetGame()->mWindowHeight * 0.5f));
	bgsc->SetScrollSpeed(Vector2(-10.0f, 0.0f));
	mBGsprites.emplace_back(bgsc);

	//�w�i3��
	bgsc = new BGSpriteComponent(this, 10);
	bgsc->SetTexture(GetGame()->GetTexture("Assets/Stars.png"));
	bgsc->SetBGSpritePos(Vector2(GetGame()->mWindowWidth * 0.5f, GetGame()->mWindowHeight * 0.5f));
	bgsc->SetScrollSpeed(Vector2(-20.0f, 0.0f));
	mBGsprites.emplace_back(bgsc);

	//�w�i4��
	bgsc = new BGSpriteComponent(this, 10);
	bgsc->SetTexture(GetGame()->GetTexture("Assets/Stars.png"));
	bgsc->SetBGSpritePos(Vector2(GetGame()->mWindowWidth * 0.5f + bgsc->GetTexWidth(), GetGame()->mWindowHeight * 0.5f));
	bgsc->SetScrollSpeed(Vector2(-20.0f, 0.0f));
	mBGsprites.emplace_back(bgsc);
}

