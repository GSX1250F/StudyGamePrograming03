#include "Game.h"
#include "Renderer.h"
#include "SoundPlayer.h"
#include "Laser.h"
#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"	
#include "CircleComponent.h"
#include "SoundComponent.h"

Laser::Laser(Game* game)
	: Actor(game)
	,mDeathTime(2.0f)
	,mLaserSpeed(900.0f)
{
	//スプライトコンポーネント作成、テクスチャ設定
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Laser.png"));
	
	//CircleComponent作成
	mCircle = new CircleComponent(this);
}

void Laser::UpdateActor(float deltaTime)
{
	//画面外にでるか、DeathTimeが0になったら消去する。
	mDeathTime -= deltaTime;
	if(mDeathTime <= 0.0f ||
	   GetPosition().x < 0.0f - GetRadius() ||
	   GetPosition().x > GetGame()->mWindowWidth + GetRadius() ||
	   GetPosition().y < 0.0f - GetRadius() ||
	   GetPosition().y > GetGame()->mWindowHeight + GetRadius())
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
				ast->SetState(EDead);
				break;
			}
		}
	}
}

void Laser::Shot()
{
	//MoveComponent作成
	MoveComponent* mc = new MoveComponent(this);
	mc->SetVelocity(mLaserSpeed * GetForward());

	//SoundComponent作成
	SoundComponent* sndC = new SoundComponent(this);
	sndC->SetChunk(GetGame()->GetSoundPlayer()->GetChunk("Assets/beam.wav"));
	sndC->SetPendingPlayChunk(5,"replay");
}

