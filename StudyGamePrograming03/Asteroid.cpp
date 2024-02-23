#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game) : Actor(game)
{
	//ランダムな位置と向きと大きさと初速で初期化
	Vector2 randPos;
	randPos.x = 1024.0f / 2.0f ; randPos.y = 768.0f / 2.0f;
	while (randPos.x > 1024.0f * 0.25f && randPos.x < 1024.0f *0.75f && randPos.y > 768.0f * 0.25f && randPos.y < 768.0f * 0.75f) 
	{
		randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
	}
	SetPosition(randPos);
	float randRot = Random::GetFloatRange(0.0f, Math::TwoPi);
	SetRotation(randRot);
	mAsteroidScale = Random::GetFloatRange(0.5f, 2.0f);
	SetScale(mAsteroidScale);
	mSpinSpeed = Random::GetFloatRange(-1.0f * Math::TwoPi, 1.0f * Math::TwoPi);
	SetSpin(mSpinSpeed);
	float randSpeed = Random::GetFloatRange(50.0f, 200.0f);
	Vector2 randVel = Vector2(Math::Cos(randRot), -Math::Sin(randRot)) * randSpeed;		//初期速度
	SetVelocity(randVel);


	//スプライトコンポーネント作成、テクスチャ設定
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	//MoveComponent作成、前進速度の設定
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(randSpeed);
	mc->SetForwardResist(0.0f);
	mc->SetSpinResist(0.0f);

	//CircleComponent作成
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(25.0f * mAsteroidScale);



	// Add to mAsteroids in game
	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}

void Asteroid::UpdateActor(float deltaTime)
{
	float spin = GetSpin();
	spin += mSpinSpeed * deltaTime;
	SetSpin(spin);
}
