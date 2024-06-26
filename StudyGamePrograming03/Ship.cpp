#include "Game.h"
#include "Ship.h"
#include "Laser.h"
#include "Asteroid.h"
#include "ClearPict.h"
#include "AnimSpriteComponent.h"
#include "InputComponent.h"
#include "Random.h"
#include "CircleComponent.h"

Ship::Ship(Game* game)
	: Actor(game)
	, mLaserCooldown(0.0f)
	, mCrashCooldown(0.0f)
	, mShipCooldown(0.0f)
	, mAsteroidCooldown(3.0f)
	, crashPos(Vector2(0.0f, 0.0f))
	, crash(false)
{
	SetScale(0.8f);

	// アニメーションのスプライトコンポーネントを作成
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

	//InputComponent作成
	mInput = new InputComponent(this);
	/*
	mInput->SetForwardKey(SDL_KeyCode::SDLK_UP);
	mInput->SetBackwardKey(SDL_KeyCode::SDLK_DOWN);
	mInput->SetClockwiseKey(SDL_KeyCode::SDLK_RIGHT);
	mInput->SetCounterClockwiseKey(SDL_KeyCode::SDLK_LEFT);
	*/
	mInput->SetMaxForwardForce(300.0f);
	mInput->SetMaxRotForce(150.0f);
	mInput->SetMoveResist(30.0f);
	mInput->SetRotResist(15.0f);
	mInput->SetMass(1.0f);

	//CircleComponent作成
	mCircle = new CircleComponent(this);
	
	Init();
}

void Ship::Init()
{
	
	SetPosition(Vector2(GetGame()->mWindowWidth / 2.0f, GetGame()->mWindowHeight / 2.0f));
	//ランダムな向きで初期化
	float rot = Random::GetFloatRange(0.0f, Math::TwoPi);
	SetRotation(rot);
	mInput->SetVelocity(Vector2::Zero);
	mInput->SetRotSpeed(0.0f);
}

void Ship::ActorInput(const SDL_Event event)
{
	if (crash == false) 
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_LEFT:
					mAnimComponent->SetAnimNum(2, 2, false);
					break;
				case SDLK_RIGHT:
					mAnimComponent->SetAnimNum(3, 3, false);
					break;
				case SDLK_UP:
					mAnimComponent->SetAnimNum(4, 4, false);
					break;
				case SDLK_DOWN:
					mAnimComponent->SetAnimNum(5, 5, false);
					break;
				case SDLK_SPACE:
					if (mLaserCooldown <= 0.0f)
					{
						// レーザーオブジェクトを作成、位置と回転角を宇宙船とあわせる。
						Laser* laser = new Laser(GetGame());
						laser->SetPosition(GetPosition() + 35.0f * GetScale() * Vector2(Math::Cos(GetRotation()), -Math::Sin(GetRotation())));
						laser->SetRotation(GetRotation());
						laser->Shot();
						// レーザー冷却期間リセット
						mLaserCooldown = 0.5f;
					}
					break;
			}
		}
		if (mAnimComponent->mIsAnimating == false)
		{
			// アニメーション中が終わっていたら元のループに戻る。
			mAnimComponent->SetAnimNum(1, 1, true);
		}
	}	
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;	//レーザーを次に撃てるまでの時間
	mAsteroidCooldown -= deltaTime;

	// 小惑星を一定時間ごとに増やす。小惑星の数が０になったらゲームクリア画面をアクティブにする。
	int numAsteroids = GetGame()->GetAsteroids().size();
	if (mAsteroidCooldown < 0.0f && numAsteroids > 0)
	{
		GetGame()->AddAsteroid();
		mAsteroidCooldown = 5.0f;
	}
	if (numAsteroids == 0)
	{
		GetGame()->GetClearPict()->SetState(EActive);
	}

	if (crash == false)
	{
		//画面外にでたら反対の位置に移動（ラッピング処理）
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
		//小惑星と衝突したかを判定
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())) && ast->GetState() == EActive)
			{
				//小惑星と衝突
				crashPos = GetPosition();
				crashRot = GetRotation();
				crash = true;
				mCrashCooldown = 2.0f;
				mShipCooldown = 2.0f;

				//ゲーム自体を終了する場合
				//GetGame()->SetRunning(false);

				break;
			}
		}
	}
	else
	{
		// 小惑星と衝突したとき
		if (GetState() == EPaused)
		{
			// 状態がEPausedのとき、リスポーンするまでの時間を計算
			mShipCooldown -= deltaTime;
			// リスポーンするまでの時間になったら、初期位置・角度にリスポーン
			if (mShipCooldown <= 0.0f)
			{
				Init();
				SetState(EActive);
				mShipCooldown = 0.0f;
				crash = false;
			}
		}
		else
		{
			// 衝突演出中
			SetPosition(crashPos);		// MoveComponentが更新されても衝突したときの位置に置きなおし
			crashRot -= 3.0f * Math::TwoPi * deltaTime;
			SetRotation(crashRot);		// MoveComponentが更新されても衝突してからの回転角度に置きなおし
			mCrashCooldown -= deltaTime;
			if (mCrashCooldown <= 0.0f)
			{
				SetState(EPaused);
				mCrashCooldown = 0.0f;
			}
		}
	}


}



