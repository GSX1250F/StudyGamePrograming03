#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	//コンストラクタ。Update Orderは早め。
	MoveComponent(class Actor* owner , int updateOrder = 10);
	~MoveComponent();

	//Updateをオーバーライド
	void Update(float deltatime) override;

	//各動作のパラメータのゲッター・セッター
	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

protected:


private:
	// 前進角速度（ラジアン / 秒）
	float mAngularSpeed;
	// 前進速度（単位長 / 秒）
	float mForwardSpeed;

};

