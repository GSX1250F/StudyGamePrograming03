#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"

Asteroid::Asteroid(Game* game) : Actor(game)
{
	//ランダムな位置と向きで初期化
	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	//スプライトコンポーネント作成、テクスチャ設定
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	//MoveComponent作成、前進速度の設定
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
