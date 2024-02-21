#pragma once
#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(Game* game);
	
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	void Init();

	class CircleComponent* GetCircle() { return mCircle; }


protected:


private:
	float mLaserCooldown;
	class CircleComponent* mCircle;		//衝突チェックのためのアクセスポインタ。他のオブジェクトから参照するため。
};

