#include "AsteroidControl.h"
#include "Game.h"

AsteroidControl::AsteroidControl(Game* game):Actor(game)
	,mAsteroidCooldown(4.0)
{
}

void AsteroidControl::UpdateActor(float deltaTime)
{
	mAsteroidCooldown -= deltaTime;
    //���f������莞�Ԃ��Ƃɑ��₷�B���f���̐����O�ɂȂ�����Q�[���N���A��ʂ��A�N�e�B�u�ɂ���B
    int numAsteroids = GetGame()->GetAsteroids().size();
    if(mAsteroidCooldown < 0.0 && numAsteroids > 0)
    {
        GetGame()->AddAsteroid();
        mAsteroidCooldown = 5.0;
    }
        
}
