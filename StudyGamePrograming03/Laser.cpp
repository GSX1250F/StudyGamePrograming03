#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"	
#include "Game.h"
#include "Asteroid.h"
#include "CircleComponent.h"

Laser::Laser(Game* game) : Actor(game),mDeathTime(2.0f)
{
	//スプライトコンポーネント作成、テクスチャ設定
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	//MoveComponent作成、前進速度の設定
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);
	mc->SetForwardResist(0.0f);
	mc->SetSpinResist(0.0f);
	

	//初期位置と角度はShipで設定

	//CircleComponent作成
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);

}

void Laser::UpdateActor(float deltaTime)
{
	//位置はMoveComponentで更新される。
	//画面外にでるか、DeathTimeが0になったら消去する。
	mDeathTime -= deltaTime;
	if(mDeathTime <= 0.0f ||
	   GetPosition().x < 0.0f ||
	   GetPosition().x > 1024.0f ||
	   GetPosition().y < 0.0f ||
	   GetPosition().y > 768.0f)
	{
		SetState(EDead);
	}
	else
	{
		//小惑星と衝突したとき
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				//レーザーも消去するなら次を実行
				SetState(EDead);

				//小惑星を消去
				ast->SetState(EPaused);

				break;
			}
		}
	}



}

