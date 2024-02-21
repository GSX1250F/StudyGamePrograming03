#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game) : Actor(game)
{
	//ランダムな位置と向きで初期化
	Vector2 randPos;
	randPos.x = 1024.0f / 2.0f ; randPos.y = 768.0f / 2.0f;
	while (randPos.x > 1024.0f * 0.25f && randPos.x < 1024.0f *0.75f && randPos.y > 768.0f * 0.25f && randPos.y < 768.0f * 0.75f) 
	{
		randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
	}
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	//スプライトコンポーネント作成、テクスチャ設定
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	//MoveComponent作成、前進速度の設定
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	//CircleComponent作成
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);


	//SpriteRotationSpeed設定
	mSpriteRotatingSpeed = Random::GetFloatRange(-2.0f, 2.0f);



	// Add to mAsteroids in game
	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}

void Asteroid::UpdateActor(float deltaTime)
{
	//Spriteだけまわす

}
