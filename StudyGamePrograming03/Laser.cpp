#include "Game.h"
#include "Laser.h"
#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"	
#include "CircleComponent.h"

Laser::Laser(Game* game) : Actor(game),mDeathTime(2.0f), mLaserSpeed(900.0f)
{
	//�����ʒu,�p�x��Ship�Őݒ�
	//�X�v���C�g�R���|�[�l���g�쐬�A�e�N�X�`���ݒ�
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));
}

void Laser::UpdateActor(float deltaTime)
{
	//�ʒu��MoveComponent�ōX�V�����B
	//��ʊO�ɂł邩�ADeathTime��0�ɂȂ������������B
	mDeathTime -= deltaTime;
	if(mDeathTime <= 0.0f ||
	   GetPosition().x < 0.0f ||
	   GetPosition().x > GetGame()->mWindowWidth ||
	   GetPosition().y < 0.0f ||
	   GetPosition().y > GetGame()->mWindowHeight)
	{
		SetState(EDead);
	}
	else
	{
		//���f���ƏՓ˂����Ƃ�
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				//���[�U�[����������Ȃ玟�����s
				SetState(EDead);

				//���f��������
				ast->SetState(EDead);
				break;
			}
		}
	}
}

void Laser::Shot()
{
	//MoveComponent�쐬
	MoveComponent* mc = new MoveComponent(this);
	mc->SetVelocity(mLaserSpeed * Vector2(Math::Cos(GetRotation()), -Math::Sin(GetRotation())));

	//CircleComponent�쐬
	mCircle = new CircleComponent(this);
}

