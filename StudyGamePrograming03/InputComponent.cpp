#include "InputComponent.h"
#include "Actor.h"


InputComponent::InputComponent(Actor* owner, int updateOrder) 
	: MoveComponent(owner)
	, mForwardKey(0)
	, mBackwardKey(0)
	, mClockwiseKey(0)
	, mCounterClockwiseKey(0)
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	//MoveComponentのための計算
	/*
	float forwardSpeed = 0.0f;
	if (keyState[mForwardKey])
	{
		forwardSpeed += mMaxForwardSpeed;
	}
	else if (keyState[mBackwardKey])
	{
		forwardSpeed -= mMaxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (keyState[mClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;		//角速度の＋方向はCCW
	}
	else if (keyState[mCounterClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;		//角速度の＋方向はCCW
	}
	SetAngularSpeed(angularSpeed);
	*/
	
	//古典物理学でMoveComponentのための計算
	//MoveComponentには前進か回転方向の力の最大値だけを渡す
	float forwardforce = 0.0f;
	if (keyState[mForwardKey])
	{
		forwardforce += mMaxForwardForce;
	}
	else if (keyState[mBackwardKey])
	{
		forwardforce -= mMaxForwardForce;
	}
	SetForwardForce(forwardforce);

	float spinforce = 0.0f;
	if (keyState[mClockwiseKey])
	{
		spinforce -= mMaxSpinForce;		//角度の＋方向はCCW
	}
	else if (keyState[mCounterClockwiseKey])
	{
		spinforce += mMaxSpinForce;		//角度の＋方向はCCW
	}
	SetSpinForce(spinforce);

}

