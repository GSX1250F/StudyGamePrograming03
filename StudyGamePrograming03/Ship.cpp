#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"		//MoveComponent�̎q�N���X�Ȃ̂ŁAMoveComponent���ǂݍ��܂��B
#include "Game.h"
#include "Random.h"
#include "Laser.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Ship::Ship(Game* game) : Actor(game) , mLaserCooldown(0.0f)
{
	Init();

	//�X�v���C�g�R���|�[�l���g�쐬�A�e�N�X�`���ݒ�
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	//InputComponent�쐬
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_UP);
	ic->SetBackwardKey(SDL_SCANCODE_DOWN);
	ic->SetClockwiseKey(SDL_SCANCODE_RIGHT);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_LEFT);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);

	//CircleComponent�쐬
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(30.0f);
	
}

void Ship::Init()
{
	//�����_���Ȍ����ŏ�����
	SetPosition(Vector2(1024.0f / 2.0f, 768.0f / 2.0f));
	float rot = Random::GetFloatRange(0.0f, Math::TwoPi);
	SetRotation(rot);
	SetSpin(rot);		//�X�s���Ɠ����]�����킹��B
	SetScale(0.7f);

	crash = false;
	crashTime = 2.0f;
	crashPos.x = 0.0f;
	crashPos.y = 0.0f;

}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		// ���[�U�[�I�u�W�F�N�g���쐬�A�ʒu�Ɖ�]�p���F���D�Ƃ��킹��B
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		// ���[�U�[��p���ԃ��Z�b�g
		mLaserCooldown = 0.5f;
	}
}

void Ship::UpdateActor(float deltaTime)
{
	if (crash == false)
	{
		SetSpin(GetRotation());			// �����]�ƃX�s�������킹��B

		mLaserCooldown -= deltaTime;	//���[�U�[�����Ɍ��Ă�܂ł̎���

		//�ʒu��MoveComponent�ōX�V�����B
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				//���f���ƏՓ˂����Ƃ�
				crashPos = GetPosition();
				crashRot = GetRotation();

				//�Q�[�����̂��I������ꍇ
				//GetGame()->SetRunning(false);

				crash = true;
				break;
			}
		}
	}
	else
	{
		if (crashTime >= 0.0f)
		{
			SetPosition(crashPos);		// MoveComponent���X�V����Ă��Փˈʒu�ɒu���Ȃ���
			crashRot -= 2.0f * Math::TwoPi * deltaTime;
			SetSpin(crashRot);		// MoveComponent���X�V����Ă��Փˊp�x�ɒu���Ȃ���
			crashTime -= deltaTime;
		}
		else
		{
			//�����ʒu�փ��Z�b�g
			Init();
		}
	}


}



