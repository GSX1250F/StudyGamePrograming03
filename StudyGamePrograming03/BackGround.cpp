#include "BackGround.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

BackGround::BackGround(Game* game)
{
	//MoveComponent作成
	MoveComponent* mc = new MoveComponent(this);
	mc->SetVelocity(Vector2(scrollspeed, 0.0f));

	//スプライトコンポーネント作成、テクスチャ設定
	SpriteComponent* sc = new SpriteComponent(this, updateorder);
	sc->SetTexture(game->GetTexture(filename));
	offset = sc->GetTexWidth();

	SetPosition(Vector2(GetGame()->mWindowWidth * 0.5f + id * offset, GetGame()->mWindowHeight * 0.5f));

	//背景をゲームに追加
	game->AddBackGround(this);
}

