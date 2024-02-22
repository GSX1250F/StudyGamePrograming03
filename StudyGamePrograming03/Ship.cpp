#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"		//MoveComponentの子クラスなので、MoveComponentも読み込まれる。
#include "Game.h"
#include "Random.h"
#include "Laser.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Ship::Ship(Game* game) : Actor(game) , mLaserCooldown(0.0f)
{
	Init();

	//スプライトコンポーネント作成、テクスチャ設定
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	//InputComponent作成
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_UP);
	ic->SetBackwardKey(SDL_SCANCODE_DOWN);
	ic->SetClockwiseKey(SDL_SCANCODE_RIGHT);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_LEFT);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxSpinSpeed(Math::TwoPi);
	ic->SetMaxForwardForce(1000.0f);
	ic->SetMaxSpinForce(10.0f * Math::TwoPi);
	ic->SetMass(10.0f);
	ic->SetRadius(GetScale());

	//CircleComponent作成
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(30.0f);
	
}

void Ship::Init()
{
	//ランダムな向きで初期化
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
		if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
		{
			// レーザーオブジェクトを作成、位置と回転角を宇宙船とあわせる。
			Laser* laser = new Laser(GetGame());
			laser->SetPosition(GetPosition());
			laser->SetSpin(GetSpin());

			// レーザー冷却期間リセット
			mLaserCooldown = 0.5f;
		}
	}
	
}

void Ship::UpdateActor(float deltaTime)
{
	if (crash == false)
	{
		
		mLaserCooldown -= deltaTime;	//レーザーを次に撃てるまでの時間

		//位置はMoveComponentで更新される。
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				//小惑星と衝突したとき
				crashPos = GetPosition();
				crashRot = GetSpin();

				//ゲーム自体を終了する場合
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
			SetPosition(crashPos);		// MoveComponentが更新されても衝突したときの位置に置きなおし
			crashRot -= 3.0f * Math::TwoPi * deltaTime;
			SetSpin(crashRot);		// MoveComponentが更新されても衝突してからの回転角度に置きなおし
			crashTime -= deltaTime;
		}
		else if (crashTime < 0.0f && deactiveTime >= 0.0f)
		{
			SetState(EPaused);
			deactiveTime -= deltaTime;
			
		}
		else
		{
			//初期位置へリセット
			Init();
		}
	}


}



