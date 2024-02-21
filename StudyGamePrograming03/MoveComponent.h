#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	//�R���X�g���N�^�BUpdate Order�͑��߁B
	MoveComponent(class Actor* owner , int updateOrder = 10);
	~MoveComponent();

	//Update���I�[�o�[���C�h
	void Update(float deltatime) override;

	//�e����̃p�����[�^�̃Q�b�^�[�E�Z�b�^�[
	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

protected:


private:
	// �O�i�p���x�i���W�A�� / �b�j
	float mAngularSpeed;
	// �O�i���x�i�P�ʒ� / �b�j
	float mForwardSpeed;

};

