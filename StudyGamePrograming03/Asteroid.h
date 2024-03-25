#pragma once
#include "Actor.h"
class Asteroid : public Actor
{
public:
	Asteroid(Game* game);
	~Asteroid();

	class CircleComponent* GetCircle() { return mCircle; }

	// アクター独自の更新処理(オーバーライド可能)
	//void UpdateActor(float deltaTime) override;

protected:

private:
	class CircleComponent* mCircle;		//衝突チェックのためのアクセスポインタ。他のオブジェクトから参照するため。
};

