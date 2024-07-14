#pragma once
#include "Actor.h"
#include "SoundComponent.h"

class Asteroid : public Actor
{
public:
	Asteroid(Game* game);
	~Asteroid();

	class CircleComponent* GetCircle() { return mCircle; }

	void UpdateActor(float deltaTime) override;

private:
	class CircleComponent* mCircle;		//衝突チェックのためのアクセスポインタ。他のオブジェクトから参照するため。
	float mAsteroidCooldown;		//復活or増殖までの待機時間
	class SoundComponent* mSDC;
};

