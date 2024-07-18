#include "Game.h"
#include "Renderer.h"
#include "Ship.h"
#include "Laser.h"
#include "Asteroid.h"
#include "SomeSpriteComponent.h"
#include "InputComponent.h"
#include "Random.h"
#include "CircleComponent.h"
#include "SomeSoundComponent.h"
#include "SoundPlayer.h"

Ship::Ship(Game* game):Actor(game)
{
	//SomeSpriteComponent�쐬
	mSSC = new SomeSpriteComponent(this,30);
	std::vector<SDL_Texture*> mtexs = {
		game->GetRenderer()->GetTexture("Assets/Ship01.png"),
		game->GetRenderer()->GetTexture("Assets/Ship02.png"),
		game->GetRenderer()->GetTexture("Assets/Ship03.png"),
		game->GetRenderer()->GetTexture("Assets/Ship04.png"),
		game->GetRenderer()->GetTexture("Assets/Ship05.png")
	};
	mSSC->SetSomeTextures(mtexs);
	
	//InputComponent�쐬
	mIC = new InputComponent(this);
	//mIC->SetMaxForwardVelocity(200.0f);
	//mIC->SetMaxRotSpeed(5.0f);
	mIC->SetMaxForwardForce(300.0f);
	mIC->SetMaxRotForce(150.0f);
	mIC->SetMoveResist(30.0f);
	mIC->SetRotResist(15.0f);
	mIC->SetMass(1.0f);
	mIC->SetForwardKey(SDL_SCANCODE_UP);
	mIC->SetBackwardKey(SDL_SCANCODE_DOWN);
	mIC->SetClockwiseKey(SDL_SCANCODE_RIGHT);
	mIC->SetCounterClockwiseKey(SDL_SCANCODE_LEFT);

	//CircleComponent�쐬
	mCircle = new CircleComponent(this);

	mSSDC = new SomeSoundComponent(this);
	std::vector<Mix_Chunk*> mchunks = {
		game->GetSoundPlayer()->GetChunk("Assets/thruster.wav"),
		game->GetSoundPlayer()->GetChunk("Assets/explosion.wav")
	};
	mSSDC->SetSomeChunks(mchunks);

	Init();
}

void Ship::Init()
{
	SetScale(0.8f);
	SetPosition(Vector2(GetGame()->mWindowWidth / 2.0f, GetGame()->mWindowHeight / 2.0f));
	//�����_���Ȍ����ŏ�����
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
	mIC->SetVelocity(Vector2::Zero);
	mIC->SetRotSpeed(0.0f);
	SetState(EActive);
	mSSC->SetVisible(true);
	mSSDC->SetPlayable(true);

	mLaserCooldown = 0.0f;
	mCrashCooldown = 0.0f;
	mCrashingTime = 0.0f;
	mCrash = false;
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (mCrash == false) 
	{
		if (keyState[mIC->GetCounterClockwiseKey()])
		{
			mSSC->SetTextureFromId(1);
			mSSDC->SetChunkFromId(0);
			mSSDC->SetPendingPlayChunk(0,"play");
		}
		else if (keyState[mIC->GetClockwiseKey()])
		{
			mSSC->SetTextureFromId(2);
			mSSDC->SetChunkFromId(0);
			mSSDC->SetPendingPlayChunk(1,"play");
		}
		else if (keyState[mIC->GetForwardKey()])
		{
			mSSC->SetTextureFromId(3);
			mSSDC->SetChunkFromId(0);
			mSSDC->SetPendingPlayChunk(2,"play");
		}
		else if (keyState[mIC->GetBackwardKey()])
		{
			mSSC->SetTextureFromId(4);
			mSSDC->SetChunkFromId(0);
			mSSDC->SetPendingPlayChunk(3,"play");
		}
		else
		{
			mSSC->SetTextureFromId(0);
		}
		
		if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
		{
			// ���[�U�[�I�u�W�F�N�g���쐬�A�ʒu�Ɖ�]�p���F���D�Ƃ��킹��B
			Laser* laser = new Laser(GetGame());
			laser->SetPosition(GetPosition() + GetRadius() * GetForward());
			laser->SetRotation(GetRotation());
			laser->Shot();
			// ���[�U�[��p���ԃ��Z�b�g
			mLaserCooldown = 0.7f;
		}		
	}	
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	mCrashCooldown -= deltaTime;
	mCrashingTime -= deltaTime;

	if (mCrash == false)
	{
		//��ʊO�ɂł��甽�΂̈ʒu�Ɉړ��i���b�s���O�����j
		if (GetPosition().x < 0.0f - 1.0f * GetRadius() ||
			GetPosition().x > GetGame()->mWindowWidth + 1.0f * GetRadius())
		{
			SetPosition(Vector2(GetGame()->mWindowWidth - GetPosition().x, GetPosition().y));
		}
		if (GetPosition().y < 0.0f - 1.0f * GetRadius() ||
			GetPosition().y > GetGame()->mWindowHeight + 1.0f * GetRadius())
		{
			SetPosition(Vector2(GetPosition().x, GetGame()->mWindowHeight - GetPosition().y));
		}
		//���f���ƏՓ˂������𔻒�
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())) && ast->GetState() == EActive)
			{
				mCrashPos = GetPosition();
				mCrashRot = GetRotation();
				mCrash = true;
				mCrashCooldown = 4.0f;
				mCrashingTime = 2.0f;
				mSSDC->SetChunkFromId(1);
				mSSDC->SetPendingPlayChunk(4,"replay");;
				break;
			}
		}
	}
	else
	{
		if (mCrashingTime > 0.0f)
		{
			SetPosition(mCrashPos);		// MoveComponent���X�V����Ă��Փ˂����Ƃ��̈ʒu�ɒu���Ȃ���
			mCrashRot -= 3.0f * Math::TwoPi * deltaTime;
			SetRotation(mCrashRot);		// MoveComponent���X�V����Ă��Փ˂��Ă���̉�]�p�x�ɒu���Ȃ���
			SetScale(GetScale() * 0.98f);
		}
		else
		{
			if (mCrashCooldown > 0.0f)
			{
				//�Փˉ��o��A���X�|�[������܂ŕ\����~
				SetState(EPaused);
				mSSC->SetVisible(false);
				mSSDC->SetPlayable(false);

			}
			else
			{
				Init();
			}
		}
	}


}



