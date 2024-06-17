#pragma once
#include "MoveComponent.h"
#include <cstdint>
#include <SDL.h>

class InputComponent : public MoveComponent
{
public:
	//�R���X�g���N�^�BUpdate Order�͑��߁B
	InputComponent(class Actor* owner, int updateOrder = 10);
	~InputComponent();

	// ���͏����i�I�[�o�[���C�h�j
	void ProcessInput(const SDL_Event event) override;

	// �v���C�x�[�g�֐��̃Q�b�^�[�E�Z�b�^�[
	void SetMaxForwardForce(float power) { mMaxForwardForce = power; }
	void SetMaxRotForce(float power) { mMaxRotForce = power; }
	float GetMaxForwardForce() { return mMaxForwardForce; }
	float GetMaxRotForce() { return mMaxRotForce; }


private:
	// �O�i�E��]�����̗͂̍ő�l
	float mMaxForwardForce;
	float mMaxRotForce;
};

