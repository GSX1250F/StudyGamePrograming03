#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game) : Actor(game)
{
	//�����_���Ȉʒu�ƌ����ŏ�����
	Vector2 randPos;
	randPos.x = 1024.0f / 2.0f ; randPos.y = 768.0f / 2.0f;
	while (randPos.x > 1024.0f * 0.25f && randPos.x < 1024.0f *0.75f && randPos.y > 768.0f * 0.25f && randPos.y < 768.0f * 0.75f) 
	{
		randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
	}
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	//�X�v���C�g�R���|�[�l���g�쐬�A�e�N�X�`���ݒ�
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	//MoveComponent�쐬�A�O�i���x�̐ݒ�
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	//CircleComponent�쐬
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);


	//SpriteRotationSpeed�ݒ�
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
	//Sprite�����܂킷

}
