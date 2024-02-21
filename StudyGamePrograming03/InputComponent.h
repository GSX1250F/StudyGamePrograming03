#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	//コンストラクタ。Update Orderは早め。
	InputComponent(class Actor* owner, int updateOrder = 10);
	~InputComponent();

	// 入力処理（オーバーライド）
	void ProcessInput(const uint8_t* keyState) override;

	// プライベート関数のゲッター・セッター
	void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackwardKey(int key) { mBackwardKey = key; }
	void SetClockwiseKey(int key) { mClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }

	float GetMaxForwardSpeed() { return mMaxForwardSpeed; }
	float GetMaxAngularSpeed() { return mMaxAngularSpeed; }
	int GetForwardKey() { return mForwardKey; }
	int GetBackwardKey() { return mBackwardKey; }
	int GetClockwiseKey() { return mClockwiseKey; }
	int GetCounterClockwiseKey() { return mCounterClockwiseKey; }

protected:



private:
	// 前進・回転速度の最大値
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;

	// 前進・後退のためのキー
	int mForwardKey;
	int mBackwardKey;

	//回転運動のキー
	int mClockwiseKey;
	int mCounterClockwiseKey;
	
};

