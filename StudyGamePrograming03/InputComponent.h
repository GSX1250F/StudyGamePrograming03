#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	//�R���X�g���N�^�BUpdate Order�͑��߁B
	InputComponent(class Actor* owner, int updateOrder = 10);
	~InputComponent();

	// ���͏����i�I�[�o�[���C�h�j
	void ProcessInput(const uint8_t* keyState) override;

	// �v���C�x�[�g�֐��̃Q�b�^�[�E�Z�b�^�[
	void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void SetMaxSpinSpeed(float speed) { mMaxSpinSpeed = speed; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackwardKey(int key) { mBackwardKey = key; }
	void SetClockwiseKey(int key) { mClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }

	float GetMaxForwardSpeed() { return mMaxForwardSpeed; }
	float GetMaxSpinSpeed() { return mMaxSpinSpeed; }
	int GetForwardKey() { return mForwardKey; }
	int GetBackwardKey() { return mBackwardKey; }
	int GetClockwiseKey() { return mClockwiseKey; }
	int GetCounterClockwiseKey() { return mCounterClockwiseKey; }

	void SetMaxForwardForce(float power) { mMaxForwardForce = power; }
	void SetMaxSpinForce(float power) { mMaxSpinForce = power; }
	float GetMaxForwardForce() { return mMaxForwardForce; }
	float GetMaxSpinForce() { return mMaxSpinForce; }


protected:



private:
	// �O�i�E��]���x�̍ő�l
	float mMaxForwardSpeed;
	float mMaxSpinSpeed;

	// �O�i�E��ނ̂��߂̃L�[
	int mForwardKey;
	int mBackwardKey;

	//��]�^���̃L�[
	int mClockwiseKey;
	int mCounterClockwiseKey;
	
	// �O�i�E��]�����̗͂̍ő�l�@�i���񃊃Z�b�g�j
	float mMaxForwardForce;
	float mMaxSpinForce;


};

