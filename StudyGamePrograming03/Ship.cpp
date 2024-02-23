#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "InputComponent.h"		//MoveComponent�̎q�N���X�Ȃ̂ŁAMoveComponent���ǂݍ��܂��B
#include "Game.h"
#include "Random.h"
#include "Laser.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Ship::Ship(Game* game) : Actor(game) , mLaserCooldown(0.0f)
{
	Init();
	/*
	//�X�v���C�g�R���|�[�l���g�쐬�A�e�N�X�`���ݒ�
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));
	*/

	// �A�j���[�V�����̃X�v���C�g�R���|�[�l���g���쐬
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
		game->GetTexture("Assets/Ship05.png")
	};
	asc->SetAnimTextures(anims,1,1,true);
	mAnimComponent = asc;


	//InputComponent�쐬
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_UP);
	ic->SetBackwardKey(SDL_SCANCODE_DOWN);
	ic->SetClockwiseKey(SDL_SCANCODE_RIGHT);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_LEFT);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxSpinSpeed(Math::TwoPi);
	ic->SetMaxForwardForce(2000.0f);
	ic->SetMaxSpinForce(20.0f * Math::TwoPi);
	ic->SetMass(10.0f);
	ic->SetRadius(GetScale());
	ic->SetForwardResist(0.00002f);
	ic->SetSpinResist(2.0f);

	//CircleComponent�쐬
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(30.0f);
	
}

void Ship::Init()
{
	//�����_���Ȍ����ŏ�����
	SetPosition(Vector2(1024.0f / 2.0f, 768.0f / 2.0f));
	float spin = Random::GetFloatRange(0.0f, Math::TwoPi);
	SetRotation(0.0f);
	SetSpin(spin);
	SetScale(1.0f);

	crash = false;
	crashTime = 1.5f;
	crashPos.x = 0.0f;
	crashPos.y = 0.0f;
	deactiveTime = 1.5f;
	SetState(EActive);
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (crash == false) 
	{
		if (keyState[SDL_SCANCODE_LEFT])
		{
			mAnimComponent->SetAnimNum(2, 2, false); 
		}
		else if (keyState[SDL_SCANCODE_RIGHT])
		{
			mAnimComponent->SetAnimNum(3, 3, false); 
		}
		else if (keyState[SDL_SCANCODE_UP])
		{
			mAnimComponent->SetAnimNum(4, 4, false); 
		}
		else if (keyState[SDL_SCANCODE_DOWN])
		{
			mAnimComponent->SetAnimNum(5, 5, false); 
		}
		else if (mAnimComponent->mIsAnimating == false)
		{
			// �A�j���[�V���������I����Ă����猳�̃��[�v�ɖ߂�B
			mAnimComponent->SetAnimNum(1, 1, true);
		}


		if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
		{
			// ���[�U�[�I�u�W�F�N�g���쐬�A�ʒu�Ɖ�]�p���F���D�Ƃ��킹��B
			Laser* laser = new Laser(GetGame());
			laser->SetPosition(GetPosition() + 35.0f * GetScale() * Vector2(Math::Cos(GetSpin()), -Math::Sin(GetSpin())));
			laser->SetSpin(GetSpin());
			laser->SetVelocity(1000.0f * Vector2(Math::Cos(GetSpin()),-Math::Sin(GetSpin())));

			// ���[�U�[��p���ԃ��Z�b�g
			mLaserCooldown = 0.5f;
		}
	}
	
}

void Ship::UpdateActor(float deltaTime)
{
	if (crash == false)
	{
		
		mLaserCooldown -= deltaTime;	//���[�U�[�����Ɍ��Ă�܂ł̎���

		//�ʒu��MoveComponent�ōX�V�����B
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				//���f���ƏՓ˂����Ƃ�
				crashPos = GetPosition();
				crashRot = GetSpin();

				//�Q�[�����̂��I������ꍇ
				//GetGame()->SetRunning(false);

				crash = true;
				break;
			}
		}
	}
	else
	{
		if (crashTime >= 0.0f && deactiveTime >= 0.0f)
		{
			SetPosition(crashPos);		// MoveComponent���X�V����Ă��Փ˂����Ƃ��̈ʒu�ɒu���Ȃ���
			crashRot -= 3.0f * Math::TwoPi * deltaTime;
			SetSpin(crashRot);		// MoveComponent���X�V����Ă��Փ˂��Ă���̉�]�p�x�ɒu���Ȃ���
			crashTime -= deltaTime;
		}
		else if (crashTime < 0.0f && deactiveTime >= 0.0f)
		{
			SetState(EPaused);
			deactiveTime -= deltaTime;
			
		}
		else
		{
			//�����ʒu�փ��Z�b�g
			Init();
		}
	}


}



