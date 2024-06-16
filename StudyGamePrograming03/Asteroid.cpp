#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game) : Actor(game)
{
	//ランダムな位置と向きと大きさと初速で初期化
	Vector2 randPos = Vector2::Zero;
	while (randPos.x > GetGame()->mWindowWidth * 0.25f && randPos.x < GetGame()->mWindowHeight *0.75f && randPos.y > 768.0f * 0.25f && randPos.y < 768.0f * 0.75f)
	{
		randPos = Random::GetVector(Vector2::Zero, Vector2(GetGame()->mWindowWidth, GetGame()->mWindowHeight));
	}
	SetPosition(randPos);
	float randRot = Random::GetFloatRange(0.0f, Math::TwoPi);
	SetRotation(randRot);
	float randScale = Random::GetFloatRange(0.5f, 2.5f);
	SetScale(randScale);
	float rotSpeed = Random::GetFloatRange(-1.0f * Math::TwoPi, 1.0f * Math::TwoPi);
	float randSpeed = Random::GetFloatRange(50.0f, 200.0f);
	Vector2 randVel = Vector2(Math::Cos(randRot), -Math::Sin(randRot)) * randSpeed;		//初期速度
	
	//スプライトコンポーネント作成、テクスチャ設定
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	//MoveComponent作成　※力は働かないでただ動かすだけなら不要。
	MoveComponent* mc = new MoveComponent(this);
	mc->SetVelocity(randVel);
	mc->SetRotSpeed(rotSpeed);

	//CircleComponent作成
	mCircle = new CircleComponent(this);

	// Add to mAsteroids in game
	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}

void Asteroid::UpdateActor(float deltaTime)
{
	//画面外にでたら反対の位置に移動（ラッピング処理）
	if (GetPosition().x < 0.0f - 2 * GetRadius() ||
		GetPosition().x > GetGame()->mWindowWidth + 2 * GetRadius() )
	{
		SetPosition(Vector2(GetGame()->mWindowWidth - GetPosition().x , GetPosition().y));
	}
	if (GetPosition().y < 0.0f - 2 * GetRadius() ||
		GetPosition().y > GetGame()->mWindowHeight + 2 * GetRadius())
	{
		SetPosition(Vector2(GetPosition().x , GetGame()->mWindowHeight - GetPosition().y));
	}
}


