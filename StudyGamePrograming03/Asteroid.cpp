#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game) : Actor(game)
{
	//�����_���Ȉʒu�ƌ����Ƒ傫���Ə����ŏ�����
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
	Vector2 randVel = Vector2(Math::Cos(randRot), -Math::Sin(randRot)) * randSpeed;		//�������x
	
	//�X�v���C�g�R���|�[�l���g�쐬�A�e�N�X�`���ݒ�
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	//MoveComponent�쐬�@���͓͂����Ȃ��ł��������������Ȃ�s�v�B
	MoveComponent* mc = new MoveComponent(this);
	mc->SetVelocity(randVel);
	mc->SetRotSpeed(rotSpeed);

	//CircleComponent�쐬
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
	//��ʊO�ɂł��甽�΂̈ʒu�Ɉړ��i���b�s���O�����j
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


