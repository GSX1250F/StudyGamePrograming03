#include "AsteroidControl.h"
#include "Game.h"

AsteroidControl::AsteroidControl(Game* game):Actor(game)
	,mAsteroidCooldown(4.0)
{
}

void AsteroidControl::UpdateActor(float deltaTime)
{
	mAsteroidCooldown -= deltaTime;
    //小惑星を一定時間ごとに増やす。小惑星の数が０になったらゲームクリア画面をアクティブにする。
    int numAsteroids = GetGame()->GetAsteroids().size();
    if(mAsteroidCooldown < 0.0 && numAsteroids > 0)
    {
        GetGame()->AddAsteroid();
        mAsteroidCooldown = 5.0;
    }
        
}
