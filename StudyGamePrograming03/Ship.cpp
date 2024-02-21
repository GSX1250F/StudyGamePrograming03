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
	ic->SetMaxAngularSpeed(Math::TwoPi);

	//CircleComponent作成
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(28.0f);

}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;	//レーザーを次に撃てるまでの時間
	
	//位置はMoveComponentで更新される。
	//小惑星と衝突したとき
	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())))
		{
			//ゲーム自体を終了する場合
			//GetGame()->SetRunning(false);

			//初期位置へリセットの場合
			Init();

			break;
		}
	}
}

void Ship::Init()
{
	//ランダムな向きで初期化
	SetPosition(Vector2(1024.0f / 2.0f, 768.0f / 2.0f));
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
	SetScale(0.7f);

}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		// レーザーオブジェクトを作成、位置と回転角を宇宙船とあわせる。
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		// レーザー冷却期間リセット
		mLaserCooldown = 0.5f;
	}
}

