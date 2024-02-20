#include "Ship.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Random.h"

Ship::Ship(Game* game) : Actor(game)
{
	//ランダムな向きで初期化
	SetPosition(Vector2(1024.0f / 2.0f, 768.0f / 2.0f));
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
	

	//スプライトコンポーネント作成、テクスチャ設定
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	//MoveComponent作成、前進速度の初期化
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(0.0f);

	//InputComponent作成
	InputComponent* mc = new InputComponent(this);
}

Ship::~Ship()
{
}
