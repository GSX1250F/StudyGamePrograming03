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
	float GetSpinSpeed() const { return mSpinSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	float GetForwardAngle() const { return mForwardAngle; }
	void SetSpinSpeed(float speed) { mSpinSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	void SetForwardAngle(float angle) { mForwardAngle = angle; }

	float GetMass() const { return mMass; }
	float GetRadius() const { return mRadius; }
	float GetForwardForce() const { return mForwardForce; }
	float GetSpinForce() const { return mSpinForce; }
	float GetForwardAccel() const { return mForwardAccel; }
	float GetSpinAccel() const { return mSpinAccel; }
	void SetMass(float mass) { mMass = mass; }
	void SetRadius(float radius) { mRadius = radius; }
	void SetSpinForce(float force) { mSpinForce = force; }
	void SetForwardForce(float force) { mForwardForce = force; }
	void SetSpinAccel(float accel) { mSpinAccel = accel; }
	void SetForwardAccel(float accel) { mForwardAccel = accel; }


protected:


private:
	// 回転速度（ラジアン / 秒）
	float mSpinSpeed;
	// 前進速度（単位長 / 秒）
	float mForwardSpeed;
	// 前進角度（ラジアン）
	float mForwardAngle;
	// 古典物理学を実装する。必要なのは、質量、前進力、回転力、前進加速度、回転加速度
	// 質量
	float mMass;
	// 半径
	float mRadius;
	// 前進力
	float mForwardForce;
	// 回転力
	float mSpinForce;
	// 前進加速度
	float mForwardAccel;
	// 回転加速度
	float mSpinAccel;
	


};

