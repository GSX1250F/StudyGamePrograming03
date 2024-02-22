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
	// ��]���x�i���W�A�� / �b�j
	float mSpinSpeed;
	// �O�i���x�i�P�ʒ� / �b�j
	float mForwardSpeed;
	// �O�i�p�x�i���W�A���j
	float mForwardAngle;
	// �ÓT�����w����������B�K�v�Ȃ̂́A���ʁA�O�i�́A��]�́A�O�i�����x�A��]�����x
	// ����
	float mMass;
	// ���a
	float mRadius;
	// �O�i��
	float mForwardForce;
	// ��]��
	float mSpinForce;
	// �O�i�����x
	float mForwardAccel;
	// ��]�����x
	float mSpinAccel;
	


};

